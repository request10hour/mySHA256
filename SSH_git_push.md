# SSH를 이용한 git 인증

참고한 글 : https://devocean.sk.com/blog/techBoardDetail.do?ID=163311

`비밀번호 인증 지원은 2021년 8월 13일에 제거되었습니다. 대신 개인 액세스 토큰을 사용하세요.`

따라서 해당 날짜 이후 git push를 위해서는 토큰을 발급받거나, ssh인증을 해야만 한다.

토큰은 잃어버리면 재발급이 귀찮다는 문제가 발생하기에 ssh 인증 방식을 선택하였다.
<br><br>

root 권한 설정
---
```shell
su
# password 입력
```
- 아래 과정 진행 시, root 권한을 가지고 시작해야 도중에 오류가 발생하는 일이 없음. 사용자 계정에서 진행하고 싶다면 sudo를 사용해야 할 듯...

<br>

ssh key 생성
---
```shell
ssh-keygen -t ed25519 -C "request10hour@gmail.com"
# 이후 나오는 모든 응답에 대해 엔터
```

- -t 옵션 : 암호화 방식 지정

  `-t type
Specifies the type of key to create. The possible values are ''rsa1'' for protocol version 1 and ''rsa'' or ''dsa'' for protocol version 2.`

  rsa, dsa 등의 암호화 방식이 올 수 있으며, ed25519가 최신 암호화 방식이라고 해서 사용해보았다.

- -C 옵션 : 코멘트 기록

  `-C comment Provides a new comment.`

<br>

ssh-agent에 키 등록
---
```shell
eval "$(ssh-agent -s)"
```
- eval : 문자열을 명령으로 인식, 실행

  `eval - construct command by concatenating arguments`

  참고) 그냥 "ssh-agent -s" 를 입력했을 때의 결과
  다음과 같은 문자열을 얻을 수 있다.
  ```shell
  root@COM1:~/# ssh-agent -s
  SSH_AUTH_SOCK=/tmp/ssh-mST1PMkNeylt/agent.1282; export SSH_AUTH_SOCK;
  SSH_AGENT_PID=1283; export SSH_AGENT_PID;
  echo Agent pid 1283;
  ```

<br>

config 파일 설정
---
```shell
vim ~/.ssh/config
```
  vim으로 파일 연 뒤, 아래 내용 붙여넣기
```shell
Host *
AddKeysToAgent yes
IgnoreUnknown UseKeychain
UseKeychain yes
IdentityFile ~/.ssh/id_ed25519
```
  이후 저장, vim종료
```shell
wq
```

<br>

ssh-agent에 ssh 개인키 추가
---
```shell
ssh-add ~/.ssh/id_ed25519
```
- 참고한 글에서는 -K 옵션을 사용하였는데,

  `-K Load resident keys from a FIDO authenticator.`

  Windows에선 해당옵션 사용시 오류가 난다. Mac에서만 사용 가능하며, Mac의 키체인에 ssh key를 등록하는 옵션이라고 한다.

<br>

ssh key 추가
---
```shell
cat ~/.ssh/id_ed25519.pub
# 나오는 내용 복사
```
Github 페이지에서)<br>
프로필 클릭 -> Settings -> SSH and GPG keys -> New SSH key

`Title` 아무거나 입력<br>
`Key type` Authentication Key<br>
`Key` 위에서 복사한 내용 붙여넣기

-> Add SSH key

<br>

키 등록 테스트
---
```shell
ssh -T git@github.com
# 정상 등록되었으면 Hi...어쩌구저쩌구 출력됨
```
`-T' Disable pseudo-tty allocation.`


이후 git repository에서 HTTPS 방식이 아닌 SSH 선택하여 진행
