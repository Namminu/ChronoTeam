# ⏳ ChronoTeam

![Unreal Engine](https://img.shields.io/badge/Unreal%20Engine-5.x-white?style=for-the-badge&logo=unrealengine&logoColor=black)
![C++](https://img.shields.io/badge/C++-17-blue?style=for-the-badge&logo=c%2B%2B)
![Language](https://img.shields.io/badge/Language-Korean-red?style=for-the-badge)

<img width="489" height="672" alt="Image" src="https://github.com/user-attachments/assets/ee2ca3dc-6105-4488-a298-3cefccb05585" />

**ChronoTeam**은 Unreal Engine을 기반으로 제작된 고퀄리티 3인칭 액션 게임 프로젝트입니다.  
C++와 블루프린트의 효율적인 결합을 통해 정교한 전투 시스템과 게임 메카닉을 구현하는 데 초점을 맞추었습니다.

---
[![ChronoTeam Gameplay](https://img.youtube.com/vi/CDN_0tAeoBU/0.jpg)](https://www.youtube.com/watch?v=CDN_0tAeoBU)
---

## 📌 프로젝트 소개
- **장르**: 3인칭 액션 (Third-Person Action)
- **개발 환경**: Unreal Engine 5 / Visual Studio 2022
- **핵심 기술**: C++, Enhanced Input, GAS, AI Behavior Tree
- **주요 특징**: 시간 차원을 활용한 독특한 전투 메카닉과 팀 단위 시너지

## 🛠 주요 구현 기능

### 1. 캐릭터 컨트롤 및 액션 시스템
- **Enhanced Input**: 유연한 키 매핑과 입력 처리를 위한 최신 입력 시스템 적용.
- **Combo System**: 애니메이션 노티파이를 활용한 정교한 콤보 판정 및 연계 공격 구현.
- **Movement**: 가속도와 마찰력을 조절하여 묵직하면서도 기민한 캐릭터 움직임 완성.

### 2. 게임 메카닉 (Mechanics)
- **Time Manipulation**: [시간 정지/역행/슬로우] 등 프로젝트의 핵심인 시간 관련 로직 구현.
- **Damage System**: 인터페이스(Interface)를 활용하여 객체 간 결합도를 낮춘 데미지 전달 체계.
- **VFX & SFX**: 타격감을 극대화하기 위한 파티클 및 사운드 큐 연동.

### 3. AI 및 환경
- **Behavior Tree & Blackboard**: 적 캐릭터의 추적, 공격, 후퇴 등 지능적인 전투 패턴 설계.
- **Navigation Mesh**: 동적인 지형에서도 최적의 경로를 찾는 길찾기 시스템.

## 📂 프로젝트 구조 (Core Folders)
```text
Source/ChronoTeam/
├── Characters/     # 캐릭터 클래스 및 컴포넌트
├── Abilities/      # 스킬 및 액션 로직
├── GameModes/      # 게임 규칙 및 상태 관리
└── UI/             # UMG 기반 HUD 및 위젯 클래스
