## IDEA+Maven搭建项目骨架

**1. 新建Maven项目：**
点击File -> New -> Project -> Maven -> 勾选 Create from archetype -> 选择 maven-archetype-webapp (**注意：此处不要错选成上面的cocoom-22-archetype-webapp**)N、

 ![这里写图片描述](https://img-blog.csdn.net/20180408143032200?watermark/2/text/aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L2toeHU2NjY=/font/5a6L5L2T/fontsize/400/fill/I0JBQkFCMA==/dissolve/70) 

 在弹出的new project 选项卡中填写GroupId和Artifactid，其中GroupID是项目组织唯一的标识符，实际对应JAVA的包的结构，是main目录里java的目录结构，ArtifactID是项目的唯一的标识符，实际对应项目的名称，就是项目根目录的名称。对于入门练习，这两项可以随意填写。 

 之后点击next 选择Maven版本**（其中IDEA 专业版自带Maven，也可以选择自己下载的maven）**。之后填写项目名称和项目地址，完成后点击Finish，完成项目骨架的创建。 

 **2. 在新建的项目中添加所需要的文件/文件夹** 

123
