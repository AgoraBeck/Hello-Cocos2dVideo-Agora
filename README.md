
1.需要自己将cocos2d-x-3.14.1放入sample中,cocos2d下。

修改cocos2dx源码的一个头文件： 打开cocos2d/cocos/renderer/CCTrianglesCommand.h文件，将TrianglesCommand类中的函数void useMaterial() const;改为virtual void useMaterial() const;

2. 从https://pan.baidu.com/s/1qYr0RZA 下载SDK并解压。 将解压文件内容，放到Demo中AgoraGamingSDK下。 

3. 填入真实 APP Id.

4. 编译. 
