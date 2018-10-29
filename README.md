# mfc_mini_game_framwork

开发环境：vs2012，Qt5.3，MySQL 

这是我用MFC写的一个游戏登录器框架，利用MFC的一些控件和GDI+完成的。<br>
后期会加入网络和MySQL的连接，不过MFC真的要过时了，打算用Qt写了。<br>
初学C++，没有什么项目经验，欢迎前辈们进行指教。<br>
运行截图:
<img src="https://raw.githubusercontent.com/Cirnoo/mfc_mini_register/master/mfc_register.png" width="450">

资源文件来源于网络：
[资源链接](https://blog.csdn.net/geniusice18/article/details/8393674)

---
2018.10.13 更新  
忘记资源文件是通过相对文件位置导入加载的了，不能被打包加载进EXE，结果导致虽然调试的时候运行正常，但是编译成EXE文件后显示一片漆黑，打开出错。  
GDI+的imgae类无法直接加载资源文件，网上参考了一下别人的方法，发现只能加载PNG图片，加载bmp文件会出现奇怪的灰度图，只能暂时先这样了，QuQ.

--- 
2018.10.28 更新
服务器网络通信部分基本完成，剩下主要就是游戏部分了，这个框架是通用的，这里将会用斗地主做一个demo。  
服务器是用Qt写的，事实证明Qt和MFC的socket类是可以正常通信的。
需要注意的是，vs使用的是GBK编码，Qt默认使用UTF-8，通信会产生乱码，由于vs不支持UTF-8，所以只能把Qt设置成gbk编码了。
gbk编码下qDebug()不支持中文输出，使用std::cout正常。
[服务器链接](https://github.com/Cirnoo/game-server)