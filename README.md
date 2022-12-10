# GenshinTianLiBattleClient

[![Windows](https://github.com/GenshinTianLiBattle/GenshinTianLiBattleClient/actions/workflows/windows.yml/badge.svg)](https://github.com/GenshinTianLiBattle/GenshinTianLiBattleClient/actions/workflows/windows.yml)

# 原神天理战网客户端

## 功能

- [ ] 连接登录战网平台
- [ ] OCR识别UID实现账号登录
- [ ] OCR识别界面等（
- [ ] ...

## 入参唤起

- [ ] 通过命令行参数唤起
- [ ] 直接打开


## 自动更新

- [ ] 检测版本更新
- [ ] API接口获取更新信息

# 模块划分

- GenshinTianLiBattleClient 战网客户端QtGUI 
- GenshinTianLiBattleClient.Core 战网客户端内核模块 [Core](https://github.com/GenshinTianLiBattle/GenshinTianLiBattleClient.Core.git)
    
    3rdpart 依赖库
    - g2BeiDou.Capture 获取游戏画面模块 [Capture](https://github.com/g2BeiDou/g2BeiDou.Capture.git)
	- libocr Ocr识别模块 [libocr](https://github.com/GengGode/libocr.git)
    - [ ] 键鼠控制模块
    - [ ] 网络库
