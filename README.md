# SCOP
.obj 파일 파싱 후 openGL을 이용한 렌더링

## SCOP 이란?
- .obj 파일에 저장된 3D 모델을 로드하고 렌더링하는 간단한 3D 객체 뷰어
- 3D 모델을 원근 투영으로 시각화하고, 객체를 회전하거나 이동시키며, 텍스처를 적용하거나 색상 모드로 전환할 수 있는 기능을 제공
- C++로 개발되었으며, OpenGL을 사용하여 렌더링을 수행

## 주요 기능
- 원근법 렌더링
  - 3D 객체를 원근법에 따라 렌더링
- 객체 회전
  - 3D 객체는 중심 축을 기준으로 회전이 가능
- 객체 이동
  - 객체는 X, Y, Z 축을 따라 양방향으로 이동 가능
- 텍스처 및 색상 모드 전환
  - 텍스처 모드와 색상 모드 간에 부드러운 전환 가능
- 기본 3D 모델 렌더링
  - .obj 파일을 파싱하여 3D 객체를 화면에 렌더링

## 설치 및 실행
### repository clone
  ```bash
   git clone <repository_url>
  ```
### project compile
  ```bash
   make
  ```
### program execute
  ```bash
  ./SCOP <path_to_obj_file> <path_to_bmp_file>
  ```

## 조작 방법
- W, A, S, D: 객체를 상하좌우로 이동
- Q, E: 객체를 Z축을 기준으로 이동
- R: 객체 회전
- T: 텍스처 모드와 색상 모드 전환

## 기술적 제약 사항
- 프로그래밍 언어
  - C++ 사용
- 렌더링 API
  - OpenGL 사용
- 외부 라이브러리
  - 외부 라이브러리는 창 관리 및 이벤트 처리에만 사용
- 사용할 수 없는 라이브러리 (직접 구현 필요)
  - 3D 객체를 불러오는 라이브러리 사용 금지 (ex: Assimp)
  - 행렬 처리 라이브러리 사용 금지 (ex: glm)
  - 이미지 로드하는 라이브러리 사용 금지 (ex: stb)
 
## 실행 결과
![스크린샷 2024-10-01 183453](https://github.com/user-attachments/assets/a8f4d372-dc83-41fd-a761-794ae594aa0d)
![스크린샷 2024-10-01 183817](https://github.com/user-attachments/assets/206ff15f-70dc-4a0a-b319-22b1b5679276)

![스크린샷 2024-10-01 183906](https://github.com/user-attachments/assets/37c02aa7-4fa4-483c-8a78-2b3bd1e84fff)
![스크린샷 2024-10-01 183731](https://github.com/user-attachments/assets/203d5525-1133-490c-864e-f8add9602792)

![스크린샷 2024-10-01 183425](https://github.com/user-attachments/assets/a5944120-712d-4320-bd64-ed0a17c86516)
![스크린샷 2024-10-01 183358](https://github.com/user-attachments/assets/19054a73-7e2d-4e06-9b79-e369ef086c86)
