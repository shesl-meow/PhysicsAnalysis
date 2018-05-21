# PhysicsAnalysis
some analysis function used for physics exipriment in data executing

## analysis.h

**that is the function you can use**

More specification message was written in the file.

## method.h

用于分析具体实验数据，包含method函数，该函数

* 传入值1：重复实验次数

* 传入值2：实验测量的数据种类数量

* 传入值3：实验数据所在文件名
	
	* 文件数据组织格式如下：

|测量|测量次数1|测量次数2|测量次数3|....|
|:--:|:--:|:--:|:--:|:--:|
|变量1|11|12|13|...|
|变量2|21|22|23|...|
|变量3|31|32|33|...|
|...|...|...|...|...|

* 传入值4（默认值为empty）：根据各个变量的测量值，得到到的二级测量值


----------


比如，当我们需要通过测量立方体的长宽高来测量立方体体积时，假设每个量测量4次，并且文件存储在"cubic.txt"中，则按以下方式调用函数：

> method(4,3,(char *)"cubic.txt",&volume)

其中volume是一个函数，它可以按以下方式定义：

> double volume(double *val,double *bia,int len=3){
>     return val[0] * val[1] * val[2];
> }


----------
     
