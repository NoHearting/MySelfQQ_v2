# 问题与解决方案

### 1、设置`QComboBox`的下拉框背景透明

* 此处`QComboBox`为了很好的美化，方便如QQ一样显示头像和账号等信息，使用了`model/view`,在项目中使用的是`QListWidget`作为其模型和视图。设置代码如下

  ```c++
  comboBoxListWidget->setFixedHeight(180);
      comboBoxListWidget->setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);
      ui->comboBoxAccount->setModel(comboBoxListWidget->model());
      ui->comboBoxAccount->setView(comboBoxListWidget);
      ui->comboBoxAccount->setMaxVisibleItems(3);         //配合CSS显示下拉框正确高度
  
      // 将视图的父窗口设置为透明的，目的是让QComboBox的下拉框透明
      ui->comboBoxAccount->view()->parentWidget()->setWindowFlags(Qt::Popup|Qt::FramelessWindowHint);
      ui->comboBoxAccount->view()->parentWidget()->setAttribute(Qt::WA_TranslucentBackground);
  
      for(int i = 0;i<5;i++){
          QString head = QString(":/test/Z:/default/Pictures/head/head%1.jpg").arg(i);
          QPixmap origin(head);
          QPixmap scaled = Zsj::scaledPixmap(origin,40,40);
          QPixmap round = Zsj::pixmapToRound(scaled,20);
          ComboBoxItemWidget * item = new ComboBoxItemWidget(round,
                                                             QString("无心-%1").arg(i),
                                                             "123512341",
                                                             "asda123",this);
  
          item->setFixedSize(235,50);
          QListWidgetItem * widgetItem = new QListWidgetItem(comboBoxListWidget);
          connect(item,&ComboBoxItemWidget::click,this,&LoginWidget::setAccountAndPassword);
          qInfo() << "connect ComboBoxItemWidget click to LoginWidget::setAccountAndPassword";
          comboBoxListWidget->setItemWidget(widgetItem,item);
          widgetItem->setSizeHint(QSize(235,50));
      }
  ```

* 当如上设置好`QComboBox`之后，在CSS里面设置其背景透明，**但是无论如何都不能让其背景透明**

* <font color=red>**解决办法**</font>

  * 添加如下代码：

    ```c++
    // 将视图的父窗口设置为透明的，目的是让QComboBox的下拉框透明
        ui->comboBoxAccount->view()->parentWidget()->setWindowFlags(Qt::Popup|Qt::FramelessWindowHint);
        ui->comboBoxAccount->view()->parentWidget()->setAttribute(Qt::WA_TranslucentBackground);
    ```

  * 再对CSS进行添加背景透明

    ```css
    #comboBoxAccount QAbstractItemView {
        outline:0px;
        height: 60px;
        background-color: rgba(255,255,255,0.9); 	/*设置透明*/
        border:none;
        selection-background-color: rgb(237,237,237);
    }
    ```

  * 效果如下：

    ![image-20201213230708401](C:\Users\ASUS\AppData\Roaming\Typora\typora-user-images\image-20201213230708401.png)

### 2、`QComboBox`设置了代理的`model/view`后其原来的函数`setCurrentText`失效

* 如第一个问题所诉，此处使用了`QListWidget`，以至于`QComboBox`的基本函数失效，**所以在点击下拉框的选项时，无法将账号数据设置到上面的`QComboBox`中**，经过很多尝试之后，发现目前**无法正面解决这个问题**.

* <font color=red>**解决办法**</font>

  * 目的是为了设置一个值显示出来，既然无法直接解决上诉问题，可以借助其他的控件来显示/输入账号。项目中选用的是一个`QLineEdit`,设置其大小和`QComboBox`一样大，直接覆盖掉原来的`QComboBox`.

  * 但是同时这里还需要一个下拉框，所以相当于用`QLineEdit`和原来`QComboBox`的下拉框组成了一个新的`QComboBox`,为了显示/隐藏下拉框，又多用了一个按钮`QPushButton`，用于打开下拉框

  * 为什么要向上诉这样一是因为`QComboBox`原来函数失效，二是对于`CSS`样式的考虑。

  * 所以现在流程变成了：点击按钮`QPushButton`,显示`QComboBox`的下拉框，同时设置`QLineEdit`和`QPushButton`的`CSS`样式,当点击其他地方或者选中了下拉框中的内容时，收起`QComboBox`的下拉框同时设置`QLineEdit`和`QPushButton`的`CSS`样式，如果选择内容的话，则将选择的数据设置到`QLineEdit`.

  * 给出控件的布局：

    ![image-20201213232258141](C:\Users\ASUS\AppData\Roaming\Typora\typora-user-images\image-20201213232258141.png)

### 3、加载QSS文件的问题

* 在设置`QMenu`的样式的时候会读取`*Menu.css`文件用于设置其样式，样式可以设置成功，但是修改文件内容后再次执行，会发现其样式并未更改。
* 上述情况对一些文件会出现，对一些文件不会出现。
* **目前不清楚为什么会发生这种情况，尚未解决**。但是读取文件是没问题的，文件的编码都是`utf-8`，要想重新加载该样式文件可以将项目重新构建运行。



### 4、菜单样式在Win10系统和Ubuntu18.04系统下表现不一样的问题

1. 菜单项目有无图标展现的样式不同  
2. 菜单直接没有了阴影，设置阴影失败
3. 

### 5、在Ubuntu18.04系统下移动窗口会出现抖动

* 问题是由于在项目中的`Frameless`类的逻辑出现问题。
* 解决办法
  * 在Linux不用`Frameless`，通过重载移动事件来实现移动

### 6、显示二级菜单有问题。二级菜单无法正确显示

* 在消息列表下显示的二级菜单会出现无法点击的问题。

  <img src="C:\Users\ASUS\AppData\Roaming\Typora\typora-user-images\image-20210105210633691.png" alt="image-20210105210633691" style="zoom:50%;" />

  主菜单和子菜单之间会有一部分空白，导致鼠标不能移动到上方。显示二级菜单失败

* 但是在联系人的好友界面则会显示成功

  ![image-20210105210801509](C:\Users\ASUS\AppData\Roaming\Typora\typora-user-images\image-20210105210801509.png)

* 其他菜单也会显示相同的问题，不知道为什么，很奇怪

* <font color=red>解决方法：</font>

  * CSS样式设置不正确，更改CSS样式就能准确显示
  * **将CSS中对菜单宽度的设置全部去掉就可以完整显示整个菜单**。出现这个错误是由于css设置的菜单宽度小于它显示子菜单所需要的最小值，造成主菜单显示不全。



### 7、移动好友/群组到其他的分组的时候出现将当前分组内的好友移动到当前分组

* 在UI设计的时期无法解决，需要加上数据之后才能进一步完善逻辑







# 坑

### 1、读取CSS文件

* 使用以下代码读取QSS文件，如果文件中出现中文则会解析出错，不能正确设置css

  ```c++
  QString ReadQStyleSheet::readQss(QString filePath)
  {
      QFile file(filePath);
      QString qss;
      if(file.open(QIODevice::ReadOnly))
      {
          QStringList list;
          QTextStream in(&file);
          while(!in.atEnd()){
              QString line;
              in >> line;
              list << line;
          }
          qss  = list.join("\n");
  //        qDebug() << qss;
          file.close();
          return qss;
      }
      else{
          qCritical() << "style file:" << filePath << "not exist";
  
      }
      return QString("");
  }
  ```

  