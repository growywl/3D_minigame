# Assignment 3: Simple 3D Coin Game

ไฟล์เกมหลักอยู่ที่:
- `src/3.model_loading/1.model_loading/1.model_loading.cpp`
- `src/3.model_loading/1.model_loading/1.model_loading.vs`
- `src/3.model_loading/1.model_loading/1.model_loading.fs`

## ฟีเจอร์ที่ทำให้ครบตามโจทย์
1. Load 3D model from files
- Scene: `resourse/interior_building_scene/scene.gltf`
- Player: `resourse/FarmerPack/Character/Farmer/SKM_Farmer_male.fbx`
- Coin: `resourse/gold_coin_low_poly/source/GoldCoin/coin.fbx`

2. Camera following player
- กล้องเป็น third-person ติดตามตำแหน่งผู้เล่นแบบ smooth
- ใช้ mouse wheel ซูมเข้า/ออกได้

3. Collision detection
- ชนขอบ map (arena bounds)
- ชน obstacle (AABB)
- ตรวจชน coin เพื่อเก็บคะแนน

## Control
- Move: `W A S D` หรือ `Arrow keys`
- Zoom camera: Mouse wheel
- Exit: `ESC`

## สิ่งที่ต้องเตรียมก่อนส่งงาน
1. โปรเจกต์ LearnOpenGL ที่ build ได้ (GLFW, GLAD, GLM, Assimp พร้อม)
2. วางไฟล์ `.cpp/.vs/.fs` นี้แทนตัวอย่าง `3.model_loading/1.model_loading`
3. ให้โฟลเดอร์ `resourse` อยู่ใน path ที่โปรแกรมเข้าถึงได้
4. รันแล้วอัดวิดีโอ/ภาพหน้าจอ (ถ้าอาจารย์ขอหลักฐานรัน)

## Git submit
```bash
git init
git add .
git commit -m "feat: simple 3D coin game with follow camera and collision"
# ใส่ URL repo ของคุณ
git remote add origin <YOUR_GIT_URL>
git branch -M main
git push -u origin main
```

หลัง push เสร็จ ให้เอา URL repo (เช่น GitHub/GitLab) ไปส่งในช่อง assignment
