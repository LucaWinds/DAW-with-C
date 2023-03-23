---README---
2학기 정보 프로젝트
WinAPI 지원 MIDI 함수인 MCI 라이브러리를 이용한 DAW 만들기
MCI(Multimedia Control Interface)는 다중 채널을 지원하기에 여러개의 사운드를 동시에 출력할 수 있다.

#include <MMsystem.h>
를 통해 MCI를 사용할 수 있다. 

---AUTHORS---
1403

---ChangeLog---
11.30 프로젝트 제출

---NEWS---
11.30 프로젝트 제출

---INSTALL---
정보 프로젝트 2학기.sln으로 Visual Studio 실행
/debug/정보 프로젝트 2학기.exe로 응용 프로그램 실행

---LICENSE---
license free

---BUGS---
심각한 오류 :
쓰레드 간 시간 차 문제 존재

일반 오류 :
MusicListen 함수 실행 도중 나가면 일부 경우 소리가 끊기지 않고 계속 재생된다.
