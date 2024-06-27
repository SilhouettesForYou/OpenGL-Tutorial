### 目录结构

🔽dependence </br>
&nbsp;&nbsp;&nbsp;&nbsp;▶️glew-2.1.0 </br>
&nbsp;&nbsp;&nbsp;&nbsp;▶️glfw-3.4.bin.WIN32 </br>
&nbsp;&nbsp;&nbsp;&nbsp;▶️glfw-3.4.bin.WIN64 </br>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;▶️include </br>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;▶️... </br>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;▶️lib-static-ucrt </br>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;▶️glfw3.dll </br>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;▶️glfw3dll.dll </br>
🔽src </br>
 &nbsp;&nbsp;&nbsp;&nbsp;▶️main.cpp </br>
▶️xmake.lua </br>

### xmake 配置

```lua
set_project("OpenGL Tutorial")
add_rules("mode.debug", "mode.release")

target("HelloOpenGL")
    set_kind("binary")
    add_files("src/*.cpp")
    add_includedirs("/dependence/glfw-3.4.bin.WIN64/include") -- include 文件
    add_includedirs("/dependence/glew-2.1.0/include")
    add_linkdirs("/dependence/glfw-3.4.bin.WIN64/lib-static-ucrt") -- gcc 编译的静态链接库目录
    add_linkdirs("/dependence/glew-2.1.0/lib/Release/Win32")
    add_linkdirs("/dependence/glew-2.1.0/bin/Release/x64")
    add_links("glfw3dll", "glew32") -- 链接 glfw 和 glew
    add_syslinks("opengl32") -- 链接系统库
```

### Notes

* 顶点着色器
  * 每个顶点运行一次
  * 确定位置
* 片段/像素着色器
  * 填充三角形的每个像素计算一次
* 为什么索引缓冲是`unsigned int`无符号的
* 错误处理
  * `glGetError`
  * 宏定义
* uniform 变量
* VAO vertex array object
  * 当空间中有多个对象、网格、顶点缓冲区等，每个都要进行绑定着色器、**绑定顶点缓冲区**、**设置顶点布局**、**绑定索引缓冲区**、调用 DrawCall 进行绘制
  * 绑定顶点缓冲区之后还要声明顶点缓冲区的布局，不同的顶点缓冲区有不同的布局
  * 实际上都是和 VAO 有关系
  * VAO 它将所有顶点绘制过程中的这些设置和绑定过程集中存储在一起
  * VAO 是否生效由配置文件类型决定的 The compalibility profile makes VAO object 0 a default object. The core OpenGL profile makes VAO object 0 not an object at all
  * 什么时候使用 VAO
    * 如果使用核心配置，就必须使用自定义的 VAO
    * 如果只使用兼容性配置，有一个默认的 VAO
* 着色器处理的步骤
  * 传入文件或者字符串，可以编译为着色器
  * 绑定和解绑着色器
  * 可以设置着色器中的不同的`uniform`
* 渲染器类
  * 调用 Draw Call 时需要顶点数组、索引缓冲区、着色器
  * 解绑不是必要的，解绑只会浪费性能
  * 正常会用材质替换着色器
* 如何通过 OpenGL 将硬盘中的 png 图片显示到屏幕上（png 并不是引擎直接使用的格式，大多数引擎都有自己的纹理格式）
  * 将图像加载到内存中——`stb_image`
  * 获取像素的数组，然后传到显存中——OpenGL
  * 通过着色器来读取纹理，并计算出真正的像素值——像素/片段着色器（绑定纹理）
  * 在 OpenGL 中，用 slots 来绑定纹理，可以一次性绑定多个纹理
    * 在 Windows 上有 32 个 slots
    * 在移动设备，Android 或 IOS 上可能会有 8 个 slots
  * OpenGL 加载纹理是从左下角开始，即左下角的坐标是`(0, 0)`，正常加载的图片是从左上角开始遍历，所以加载图片后需要垂直翻转
  * 纹理坐标
    * 指定每个顶点对应的纹理是什么，根据顶点对应的**纹理坐标**进行采样
    * 片段着色器会根据要渲染的像素的位置，进行插值计算具体的颜色值
* 混合
  * Blending determies how we combine our output color with what is already in our target buffer
    * Output: the color we output from our fragment shader 从片段着色器中输出的颜色 **SRC**
    * Target buffer: the buffer our fragment shader is drawing to 已经存在的缓冲区上的颜色 **DEST**
  * 如何控制混合
    * `glEnable`、`glDisable`
    * `glBlendFunc(src, dest)`
      * src: how the src RGBA factor is computed (default is `GL_ONE`) 默认是 1，每个通道都是单独计算的
      * dest: how the dest RGBA factor is computed (default is `GL_ZERO`) 默认是 0，也就是说 src 会覆盖到 dest 上面
    * `glBlendEquation(mode)`
      * mode: how we combine the src and dest colors
      * Default value is `GL_FUNC_ADD`
* 投影矩阵
  * 投影就是在多维空间中确定坐标系
  * 将场景中三维空间中的坐标转换到NDC（Normalized Device Coordinates），即标准空间
  * 在窗口中渲染的内容的坐标范围必须从左到右在`[-1, 1]`之间，从上到下在`[-1, 1]`之间
  * 投影矩阵的作用就是决定坐标空间是什么样的
    * 无论是正交（Orthographic）处理后的顶点，还是透视（Perspective）处理后的顶点，最终都会映射到标准空间中
* 视图矩阵 相机的变换（位移和方向）
* 模型矩阵 对象的变换（位移、旋转、缩放，TRS）
* ImGUI

### APIs

* `glGenBuffers` 
* `glBindBuffer`
* `glBufferData`
* `glVertexAttribPointer`: 将 CPU 的数组缓冲区绑定到 GPU 的顶点缓冲区
* `glGetError`
* `glGenTextures`
* `glBindTexture`
* `glTexParameteri`
* `glTexImage2D`
* `glActiveTexture`