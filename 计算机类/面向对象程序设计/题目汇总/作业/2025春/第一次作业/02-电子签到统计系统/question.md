# 电子签到统计系统

- 题组：第一次作业
- 原始页面：https://oj.cs.tsinghua.edu.cn/course/70/contest/731/problem/2

### 题目描述

为了加强课程管理，我们需要开发一部电子签到统计系统来统计考勤情况。

系统要求：

- 从输入文件中读取参与课程的学生的名字。
- UPDATE功能，新增一节课并记录考勤
- QUERY功能，查询所有学生的考勤情况
- CHECK功能，查询指定学生的考勤情况

你需要实现两个类，ClassSystem和Student。ClassSystem负责管理一门课的考勤记录，Student负责记录学生的信息。具体的接口参考我们提供的main.cpp。

### 输入样例

第一行是参与课程的学生总数n。

接下来n行是对学生信息的描述，每行是一名同学的名字。

接下来是若干课程操作。

UPDATE m：新完成1课时的教学内容，该课时参与签到的学生数量为m，之后的m行，每行是一名签到学生的名字。

QUERY：要求输出n行，内容是到当前询问为止，每位同学的的考勤情况。每行包含学生的名字，出勤次数和缺勤次数。输出顺序按照学生参与课程的顺序，即输入文件2~n+1行的名字顺序。

CHECK name：要求输出1行，内容是到当前询问为止，名字为name的同学的考勤情况。包含学生的名字，出勤次数和缺勤次数。

END：课程操作结束，退出程序执行。

**注意：由于参与课程的助教认真负责，所以数据无需进行特殊判断，均是合法输入。**

​

```
5
A
B
C
D
E
UPDATE 3
A
B
C
UPDATE 3
A
D
B
UPDATE 3
A
B
E
UPDATE 4
A
C
B
D
QUERY
CHECK E
UPDATE 5
A
B
C
D
E
END
```

### 输出样例

```
A 4 0
B 4 0
C 2 2
D 2 2
E 1 3
E 1 3
```

### 要求

在下列代码的基础上，编写Student类（学生类）和ClassSystem类（课程系统类）的代码，完成上述要求。

main.cpp:

```
#include "Student.h"
#include "ClassSystem.h"
#include <iostream>
#include <string>

using namespace std;

int main() {

    ClassSystem oop;

    string name;
    int n;
    cin >> n;

    for(int i = 0; i < n; i++) {
        cin >> name;
        Student stu(name);
        oop.addStudent(stu);
    }

    string opt;
    while (cin >> opt) {
        if (opt == "UPDATE"){
            oop.addClassNumber();
            int total;
            cin >> total;
            for (int i = 0; i < total; i++){
                cin >> name;
                oop.signIn(name);
            }
        } else if (opt == "QUERY"){
            for (int i = 0; i < n; i++){
                Student stu = oop.getStudentById(i);
                cout << stu.getName() << " " << stu.getPresentTimes() << " " << stu.getAbsentTimes() << endl;
            }
        } else if (opt == "CHECK"){
            cin >> name;
            Student stu = oop.getStudentByName(name);
            cout << stu.getName() << " " << stu.getPresentTimes() << " " << stu.getAbsentTimes() << endl;
        } else break;
    }

    return 0;
}
```

### 提交格式

你需要提交多个文件，包含Makefile，上述文件调用的各种头文件及其cpp文件；可以不包括提供的main.cpp文件。使用Makefile能生成可执行文件main（不带扩展名）。

你应该将你的文件打包成一个zip压缩包并上传。**注意：你的文件应该在压缩包的根目录下，而不是压缩包的一个子文件夹下。**评测时，OJ会将提供的main.cpp贴入你的目录下进行编译并执行。

### 评分标准

OJ评分占100%。
