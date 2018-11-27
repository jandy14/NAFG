(N)etwork(A)ction(F)ighting(G)ame

데모 파일==================================

https://drive.google.com/open?id=1tSI42D3585qAimDeeYjZKzljkDS49eSw


게임 설명==================================

공격을 상대에게 맞추는 네트워크 대전 게임

게임 조작==================================

KetSetting.txt 를 통해 지정해줄수 있다
값은 가상키코드표의 10진수 값을 입력

상하좌우이동
베기
레이저볼
미사일
대쉬

게임 방법==================================

Host는 Host버튼을 누르고 Guest를 기다린다
Guest는 Host의 아이피를 입력해 접속한다

(이동)    : 키를 누를면 플레이어가 이동한다

(베기)    : 근거리 공격으로 일정이상의 게이지가 있어야 사용가능하다
            단 사용후 잠시동안 게이지가 오르지 않는다
(레이저볼): 공격범위가 표시되며 일정시간후 발사된다
            미사일도 파괴가능하다.
(미사일)  : 적의 위치로 유도되어 날아간다
            레이저에 파괴될 수 있으며 미사일끼리도 격추된다
(대쉬)    : 일정시간동안 빠르게 이동가능하다

플레이어 주변에는 현재 게이지의 상태를 나타내는 오라가 생긴다
이는 상대에게도 보인다 (우측상단의 게이지는 보이지 상대에게 보이지 않는다)

게임 설정==================================

GameSetting.txt라는 파일을 통해 게임에 변화를 줄 수 있다.

Color는 RGB값을 가지며 상대의 색값이 1000000이상이면 상대가 설정한 색으로
상대의 색이 정해진다.

그외의 값들은 최대한 직관적으로 적어놨으니 알아서 잘 이해하길 바란다

값을 게임 프로그램 시작시에 읽어들이므로 재설정시 게임을 껏다 켜야한다

색이외의 값들은 Host를 기준으로 하며 Guest의 값은 영향을 주지 않은다


게임 종료==================================

윈도우 종료버튼을 누르면 종료되며 상대가 종료해도 게임은 종료된다


게임 기본값================================

PlayerColor : FF0000
OpponentColor : 0000FF
PlayerSpeed : 100
PlayerMaxGauge : 300
PlayerChargingSpeed : 30
BladeDelay : 0.3
PlayerDashSpeed : 170
GaugeStopTime : 0.5
PlayerDashTime : 1.0
BladeMinRequirement : 100
BladeCost : 0
DashCost : 50
BallCastingTime : 1.0
BallDurationTime : 1.0
BallCost : 50
MissileLifeTime : 5.0
MissileSpeed : 90
MissileCost : 100
HostStartPointX : 50
HostStartPointY : 50
GuestStartPointX : 750
GuestStartPointY : 550
StartGaugeAmount : 100
