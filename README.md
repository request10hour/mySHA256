# mySHA256

1일차 :
---
my_sqrt 함수 - 제곱근 구하기<br>
my_cbrt 함수 - 세제곱근 구하기<br>
nthprime 함수 - n번째 소수 찾기<br>

위에서 구현한 세 함수를 조합하여 SHA-256 암호화에 사용되는 H 및 K 값 구하기 단위테스트로 동작 확인

추가할내용) Newton–Raphson method 란 무엇인지

2일차 :
---
my_memmove 함수 - double형을 unsigned long long에 비트옮기기 가능(형변환X)<br>
preprocess.c - 원본 텍스트 -> chunk값 -> W값<br>
Makefile - 상위 디렉토리에서 make 명령 실행으로 하위 디렉토리 makefile의 구성을 로드할 수 있게 설정함<br>
initialize 작업 진행중...H값, K값, W값을 한군데로 모으기 위해...<br>
- 진행 도중 깨달은 점<br>
  >두 가지 방식으로 franctional part를 구할 수 있다.<br>

  - 1일차에 단위 테스트 구현을 진행하며 사용한 방법은 다음과 같다.<br>
	  ```c
	  // H값 구하기
	  double sqr;
	  int a;
	  for (unsigned int i = 0; i < 8; i++)
	  {
	  	sqr = my_sqrt(nthprime(i + 1));
	  	a = (unsigned)((sqr - (int)sqr) * 0x100000000);
	  	printf("%08x\n", a);
	  }
	  ```
	  1. n번째 소수의 제곱근을 double형 변수에 받는 것으로 시작한다.
	  2. 이후 double 값의 정수 부분을 완전히 날려버린다.
	  3. 소수 부분만 남은 double 값에 `0x100000000(2의 32승)`을 곱한다.
	  4. 해당 값을 unsigned로 캐스팅 후, int형 변수에 넣는다. (자동으로 비트 자릿수가 잘려나간다.)
	  5. printf를 사용하여 해당 int형 변수를 hex로 출력하니 정상적인 결과가 도출되었다.

	<br>
	위의 방법은 덧셈과 곱셈의 연산만으로 이루어져 속도 면에서 이점이 있을 것으로 추정된다.<br>이렇게 공식화시킨 방법 이외에 조금은 비효율적일지라도, 다른 방법도 개발해보고 싶었다. <br><br>
  - 2일차에 initialize 작업을 진행하며 사용한 방법은 다음과 같다.<br>
	  ```c
	  double sqr;
	  unsigned long long a;
	  for (unsigned int i = 0; i < 8; i++)
	  {
	  	sqr = my_sqrt(nthprime(i + 1));
	  	while (sqr >= 2)
	  		sqr--;
	  	my_memmove(&a, &sqr, sizeof(unsigned long long));
	  	unsigned int b = 0xffffffff & (a >> 20);
	  	printf("%08x\n", b);
	  }
	  ```
	  1. 마찬가지로, n번째 소수의 제곱근을 double형 변수에 받는 것으로 시작한다.
	  2. 이후 double 값을 `1.xxxx`로 맞춘다. ex) 4.358898943540673 -> 1.358898943540673
	  3. 이후 `memmove`함수(해당 주소로부터 메모리 복사)를 사용하여 double형 변수 내부의 비트들을 그대로 unsigned long long형 변수로 옮겨줄 수 있다. (double형은 비트연산을 사용할 수 없기 때문)
	  4. `64비트`(8바이트) 크기의 double에서, `1비트`의 sign bit, `11비트`의 integer part, `52비트`의 franctional part로 구성되어있음을 이해한다.
	  5. 목표는 13번째 ~ 44번째 사이 총 32비트를 가져와야 한다.
	  6. 총 64비트인 자료형에서 44번째 비트 까지만 필요하므로, 마지막 20비트는 필요없기 때문에 오른쪽으로 20비트만큼 비트 시프트 해준다.
	  7. 이후 `0xffffffff`(32비트 모든 자리가 1로 채워진 상태)와 AND 연산을 수행한다. 연산 결과는 unsigned int형(4바이트) 변수에 담는다.
	  8. printf를 사용하여 해당 unsigned int형 변수를 hex로 출력하니 정상적인 결과가 도출되었다.

	<br>
	두 번째 방법으로 개발을 진행하며 크기가 다른 변수들을 비트 단위로 다루어보는 연습을 할 수 있었다. 그리고 double 자료형에서의 franctional part에 대한 이해도를 높힐 수 있었다.<br>
	심지어 본 프로젝트는 외부 라이브러리의 사용을 지양하고 있는데, memmove를 직접 구현해본 것 또한 큰 의미가 있다고 생각한다.

3일차:
---
추가할 내용)
h및 k값의 initialize 과정
w값의 연산 과정
define을 이용한 매크로 함수 이용
HKW 정상적으로 설정되었는지 중간 통합 테스트 진행

`preprocess/preprocess.c`
```c
#define RIGHTROTATE(uint, num) ((uint >> num) | (uint << 32 - num))
#define RIGHTSHIFT(uint, num) (uint >> num)

```

`initialize.c`
```c
#include <stdio.h>
#define EXTRACT_BINARY_UNITS(var) (var & 0x01 ? 0x01 : 0x00)
#define BINARY32PRINTF(var) for (size_t j = 0; j < 32; j++) printf("%d", EXTRACT_BINARY_UNITS(var >> (31 - j)))
```

compression 작업 -> sha256을 문자열로 바꾸는 작업 -> 출력까지 진행
사실 문자열출력이 아니라 메모리공간에 저장하고싶지만...malloc 사용 없이는 힘들듯...
