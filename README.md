# Simple 3D Coin Game (LearnOpenGL)

https://github.com/user-attachments/assets/bf8270e8-4fb6-474a-b5cb-83fe0ee52ac1

โปรเจกต์นี้พัฒนาต่อจาก `3.model_loading/1.model_loading` โดยทำเป็นมินิเกมเก็บเหรียญให้ครบตามโจทย์:
- โหลดโมเดล 3D จากไฟล์
- กล้องติดตามผู้เล่น
- ระบบชน (collision detection)

## Demo Features
- Player model: `Farmer` (FBX)
- Coin model: `coin` (FBX)
- พื้นและกำแพงสร้างเองในโค้ด (textured arena)
- เก็บเหรียญครบแล้วขึ้น `You Win!` ที่ title bar

## Requirement Mapping (ตรงโจทย์)
1. Load 3D model from files
- `resources/FarmerPack/Character/Farmer/SKM_Farmer_male.fbx`
- `resources/gold_coin_low_poly/source/GoldCoin/coin.fbx`

2. Camera following player
- กล้องแบบ third-person ตามผู้เล่นแบบ smooth
- Scroll mouse wheel เพื่อซูมเข้า/ออก

3. Collision detection
- ชนขอบสนาม (arena bounds)
- ตรวจชนเหรียญเพื่อเก็บคะแนน

## Controls
- Move: `W A S D` หรือ `Arrow keys`
- Zoom: `Mouse wheel`
- Exit: `ESC`

## Project Files
- `src/3.model_loading/1.model_loading/1.model_loading.cpp`
- `src/3.model_loading/1.model_loading/1.model_loading.vs`
- `src/3.model_loading/1.model_loading/1.model_loading.fs`

## Assets Needed
ให้มีไฟล์เหล่านี้ใน `LearnOpenGL-master/resources` (หรือ `resourse` ได้ เพราะโค้ดมี fallback):
- `FarmerPack/Character/Farmer/SKM_Farmer_male.fbx`
- `gold_coin_low_poly/source/GoldCoin/coin.fbx`
- `interior_building_scene/textures/FloorTiles_baseColor.jpeg`
- `interior_building_scene/textures/WoodTrim_baseColor.jpeg`

## Build/Run (CLion)
1. วางไฟล์ source/shader ไปที่บท `3.model_loading/1.model_loading`
2. Reload CMake Project
3. Build target: `3.model_loading__1.model_loading`
4. Run

## Known Notes
- โมเดลผู้เล่นยังเป็น **static pose** (ไม่มี skeletal animation runtime)
- ถ้าตัวละครหันกลับด้านในบาง asset ให้ปรับ offset มุมที่บรรทัดคำนวณ `playerYaw`
