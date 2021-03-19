# Build 安装

## Windows

参考git仓库上的说明：<https://github.com/pmem/pmdk>

### 依赖安装

参考：<https://github.com/pmem/pmdk#windows>

![](images/Markdown-image2021-03-17-19-29-54.png)

先安装`visual studio 2015+`

然后在visual studio installer中安装第1和第2个依赖，可以在`单个组件`中搜索。

第4个之间点击进去下载安装包安装即可。

第3和第5个暂时不管。

### 编译安装

参考：<https://github.com/pmem/pmdk#building-pmdk-on-windows>

注意使用常规方式打开的终端，可能提示命令`devenv`找不到。解决方式是使用visual studio打开pmdk源码项目，然后在visual studio中打开终端，进行相应的命令操作。

最后还是会打开一个visual studio，然后按`ctrl+shift+B`开始构建。

### 可能出现的问题

1. 文件libpmemobj.lib找不到，原因是生成该文件时失败了，将警告当成错误，解决方法是将该解决方案的警告等级改成最低。修改的地方在：属性 > C++ >

![](images/Markdown-image2021-03-17-20-15-08.png)

![](images/Markdown-image2021-03-17-20-14-08.png)

上面是修改后的情况，左边有个红色√的标志，下面两个则没有。

然而错误的情况还是有，因为里面有很多类似的解决方案，一个个设置也太繁琐。仔细看警告的内存，原来是有些编码不能识别，点击错误代码，会打开一个网页，里面有说解决方案。具体是将该文件另存，然后设置编码格式为如下图所示（**带签名**）：

![](images/Markdown-image2021-03-17-20-33-59.png)

然而具体在代码中怎么用，不太清楚，后续有空再搞。

## Ubuntu

