# 项目说明
  **该项目用于入门学习OSG**

# 使用说明
1. 本项目使用配置：VS2019-x64-Debug
2. 系统变量设置
+ OSG_SCREEN：在使用多屏幕时，保证只显示在一个屏幕上
```
变量名：OSG_SCREEN
变量值：0
```
+ OSG_WINDOW：不使用全屏显示，固定窗口尺寸
```
变量名：OSG_WINDOW
变量值：100 100 1000 800
```
+ OSG_FILE_PATH：OSG的数据搜索路径，存在多个data文件，可以通过“;”分隔，变量值需要配置两个路径，一个是自定义的数据路径，另一个是使用OSG的数据包的路径
```
变量名：OSG_FILE_PATH
变量值：xxx/myData;xxx/OpenSceneGraph-Data
```