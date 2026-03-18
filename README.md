# Simple 3D Coin Game (LearnOpenGL)

[https://github.com/user-attachments/assets/bf8270e8-4fb6-474a-b5cb-83fe0ee52ac1](https://github.com/user-attachments/assets/c102b555-03f3-4dec-8df3-3304206d0a32)

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

## Assets 
- `FarmerPack/Character/Farmer/SKM_Farmer_male.fbx`
- `gold_coin_low_poly/source/GoldCoin/coin.fbx`
- `interior_building_scene/textures/FloorTiles_baseColor.jpeg`
- `interior_building_scene/textures/WoodTrim_baseColor.jpeg`

## Known Notes
- โมเดลผู้เล่นยังเป็น **static pose** (ไม่มี skeletal animation runtime)

## Assets / Credits
Special Thanks to:
-- Farmer Character Model  
  Source: https://www.fab.com/listings/262fde27-6950-4030-b2b7-82892d406471 
  Author: Unreal Engine 
  License: CC-BY 4.0  

- Gold Coin Model  
  Source: [https://sketchfab.com/... ](https://sketchfab.com/3d-models/lowpoly-gold-coin-34794c00e9d140f6b86e930fef18b009) 
  Author: BlobFortress 
  License: CC-BY 4.0

-Based code & texture
  source: https://github.com/JoeyDeVries/LearnOpenGL


