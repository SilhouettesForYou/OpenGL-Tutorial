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
  * 将场景中三维空间中的坐标转换到 NDC（Normalized Device Coordinates），即标准空间
  * 在窗口中渲染的内容的坐标范围必须从左到右在`[-1, 1]`之间，从上到下在`[-1, 1]`之间
  * 投影矩阵的作用就是决定坐标空间是什么样的
    * 无论是正交（Orthographic）处理后的顶点，还是透视（Perspective）处理后的顶点，最终都会映射到标准空间中
* 视图矩阵 相机的变换（位移和方向）
* 模型矩阵 对象的变换（位移、旋转、缩放，TRS）
* ImGui
  * 测试框架
    * 声明周期
    * 封装 ImGui
* 批渲染
  * 在一次 DrawCall 中渲染多个对象

<center>
    <img src="doc/batch-rendering.jpg" />
</center>

#### 纹理的批渲染

* 颜色是uniform变量可以放到顶点缓冲中，但是不能把纹理放到顶点缓冲区中
* 但是可以像颜色一样提供纹理索引，这个索引在渲染Quad时，从顶点着色器传到片段着色器
* 片段着色器用作纹理数组和采样数组这些uniform的索引

C++ 代码中定义

```C++
// (x, y, x) 表示坐标
// (r, g, b, a) 表示颜色
// (u, v) 表示纹理
// texture_index 就是上面说的纹理索引，对应纹理槽位
float vertices[] = {
  x, y, z, r, g, b, a, u, v, texture_index_1,
  ...
  x, y, z, r, g, b, a, u, v, texture_index_2,
}
```

Shader 中的定义

```glsl
// vertex.shader
layout (location = 0) in vec3 position;
layout (location = 1) in vec4 color;
layout (location = 2) in vec2 texCoord;
layout (location = 3) in float texIndex;

...

out vec4 _color;
out vec2 _texCoord;
out float _texIndex;

// fragment.shader
layout (location = 0) out vec4 color;

uniform sampler2D textureSamplers[2];

in vec4 _color;
in vec2 _texCoord;
in float _texIndex;

void main()
{
  int index = int(_texIndex);
  color = texture(textureSamplers[index], _texCoord); // 根据索引进行采样
}
```

将纹理和槽绑定，利用uniform传递数据到shader

```c++
glBindTextureUnit(0, texture1);
glBindTextureUnit(1, texture2);

auto loc = glGetUniformLocation(shader->GetRenderId(), "textureSamplers");
int samplers[2] = { 0, 1 };
glUniform1iv(loc, 2, samplers);
```

#### 动态批量渲染

预先分配好最大的顶点缓冲区的大小（比如1KB）

* 将顶点数组用结构化的方式表示

```c++
struct Vertex
{
  float Position[3];
  float Color[4];
  float TexCoords[2];
  float TexId;
}
```

* 绑定缓冲数据时使用`GL_DYNAMIC_DRAW`类型
* 绑定顶点属性时`offset`使用内置函数`offsetof`来确定每种数据类型的偏移量

```c++
glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * 1000, nullptr, GL_DYNAMIC_DRAW);
...
glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void*)offsetof(Vertex, Position));
glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void*)offsetof(Vertex, Color));
glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void*)offsetof(Vertex, TexCoords));
glVertexAttribPointer(3, 1, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void*)offsetof(Vertex, TexId));
```

* 动态绑定顶点缓冲

```c++
// 一个quad需要四个点
std::array<Vertex, 4> CreateQuad(float x, float y, float texId)
{
  Vertex v0;
  ...
  Vertex v1;
  ...
  Vertex v2;
  ...
  Vertex v3;
  ...
  return { v0, v1, v2, v3 };
}

auto q0 = CreateQuad(-1.5f, -0.5f, 0.0f);
auto q1 = CreateQuad(0.5f, -0.5f, 1.0f);

// 通过内存拷贝的方式直接将`std::array`中的内容拷贝到一维数组中
Vertex vertices[8];
memcpy(vertices, q0.data(), q0.size() * sizeof(Vertex));
memcpy(vertices + q0.size(), q1.data(), q0.size() * sizeof(Vertex));
...
glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
```

### APIs

* `glGenBuffers`
* `glBindBuffer`
* `glBufferData`: 用来把用户定义的数据复制到当前绑定缓冲的函数
  * `GLenum target`: 目标缓冲的类型
  * `GLsizeiptr size`: 传输数据的大小(以字节为单位)，一般用`sizeof()`函数
  * `const void * data`: 实际数据
  * `GLenum usage`: 显卡如何管理给定的数据
    * `GL_STATIC_DRAW`: 数据不会或几乎不会改变
    * `GL_DYNAMIC_DRAW`: 数据会被改变很多
    * `GL_STREAM_DRAW`: 数据每次绘制时都会改变
* `glVertexAttribPointer`: 将 CPU 的数组缓冲区绑定到 GPU 的顶点缓冲区
  * `GLuint index`: Specifies the index of the generic vertex attribute to be modified 顶点属性的位置
  * `GLint size`: Specifies the number of components per generic vertex attribute. Must be 1, 2, 3, 4. Additionally, the symbolic constant `GL_BGRA` is accepted by `glVertexAttribPointer`. The initial value is 4 顶点每个属性的元素数量，一定是1，2，3，4中的一个数。~~当`type`为`GL_BGRA`时，初始值是4~~
  * `GLenum type`: Specifies the data type of each component in the array. 顶点每个属性的元素的数据类型枚举
  * `GLboolean normalized`: Specifies whether fixed-point data values should be normalized (`GL_TRUE`) or converted directly as fixed-point values (`GL_FALSE`) when they are accessed 如果设置为`GL_TRUE`，所有数据都会被映射到`[0, 1]`之间（对于有符号类型的数据是`[-1, 1]`之间）
  * `GLsizei stride`: Specifies the byte offset between consecutive generic vertex attributes. If stride​ is 0, the generic vertex attributes are understood to be tightly packed in the array. The initial value is 0 在顶点若干属性中两个相同属性之间的步长，如果步长是0
  * `const void * pointer`: Specifies a offset of the first component of the first generic vertex attribute in the array in the data store of the buffer currently bound to the `GL_ARRAY_BUFFER` target. The initial value is 0. 每个顶点属性相对于起始属性的偏移量的指针的位置
* `glGetError`
* `glGenTextures`
* `glBindTexture`
* `glTexParameteri`
* `glTexImage2D`
* `glActiveTexture`
* `glClear`
  * 不调用`glClear`的话，下一帧的内容会和上一帧的内容重叠在一起，上一帧的物体还在原来的地方
  * `glClearColor`
    * 指定刷新颜色缓冲区时所用的颜色
    * `glClearColor`只是设置缓冲区颜色，并不不会清除缓冲区的颜色，需要在设置好颜色之后调用`glClear`才会刷新缓冲区的颜色
    * `glClearColor`并不是必须的
* `glUniform1iv`
