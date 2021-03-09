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

### 6、显示二级菜单有问题。二级菜单无法正确显示  *

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

### 8、聊天界面变化时聊天记录控件的变化出现问题

* 出现的问题：

  ![image-20210125212949464](C:\Users\ASUS\AppData\Roaming\Typora\typora-user-images\image-20210125212949464.png)

  消息的气泡窗口的`resizeEvent`没有触发，所以没有适应

* 当前的解决办法：

  ```c++
  // Frameless.cpp eventFilter函数中
  
  auto geo = cacheWidget->geometry();
  widget->setGeometry(geo);
  // 设置两次是为了解决聊天窗口（ChatWidget）的聊天记录的大小在窗口变化的时候不跟着变化
  // 只有再次改变窗口大小才跟着变化，所以这里多设置一次
  // 权宜之计
  widget->setGeometry(geo.x(),geo.y(),geo.width()+1,geo.height()+1);
  ```

  只是简单的解决办法，还是会出现这个问题，只是出现的频率变小了。目前不知道什么原因

### 9

### 10、聊天界面的QSplitter无法同步

![image-20210226113815120](C:\Users\ASUS\AppData\Roaming\Typora\typora-user-images\image-20210226113815120.png)

用户聊天和群组聊天的`QSplitter`不能同步。

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

# 二、功能模块

## 1、表情功能

### （1）概要

能够显示表情，并能选择表情。界面如QQ

![image-20210221140115764](C:\Users\ASUS\AppData\Roaming\Typora\typora-user-images\image-20210221140115764.png)

### （2）选择的容器

**`QTableWidget`**+**`QLabel`**

### （3）实现方式

* 由于当前文件夹内的表情的大小是`56x56`的，而实际需要显示的大小是`24x24`的，所以有两种解决办法：

  1. 使用`QLabel`的`setPixmap`方法设置表情，但是在设置之前先将表情缩小到`24x24`。<font color=red>当前采用的方法</font>
  2. 先将所有的表情都缩小到`24x24`，然后再直接使用`setPixmap`方法

* 考虑到后续表情的数量会增加，所以需要动态的读取表情的个数

  * 读取表情个数

    1. ~~直接读取表情文件夹。虽然可以实时的改变表情的个数，但是可能会因为更改而出现问题。~~
    2. ~~通过项目的资源文件夹中的读取。资源文件会编译到可执行文件，用户无法修改，如果需要添加表情则需要重新编译打包。~~
    3. 通过`QDirIterator`读取当前项目下的所有目录和文件，找到同一前缀的所有表情。 <font color=red>当前采用的方法</font>
    4. <font color=blue>1,2两个方法都不行,因为程序编译打包之后找不到qrc文件，所有的图片资源都已经被编译成二进制代码中了。绝对路径读取文件无移植性，不采用</font>

  * 直接获取表情的qrc路径

    ```c++
    QVector<QString> EmojiTableWidget::readAllEmoji(QString pathPrefix)
    {
        QVector<QString> resultEmojiList;
        QDirIterator it(":/" + pathPrefix, QDirIterator::Subdirectories);
    
        while (it.hasNext())
        {
            QString name = it.next();
            QFileInfo fileInfo = it.fileInfo();
            if (fileInfo.isFile()) // Do not add directories to the list
            {
                resultEmojiList.push_back(name);
            }
        }
        return resultEmojiList;
    }
    ```

  * **<font color=red>动态读取表情有一个大问题。就是没办法为每一个表情设置一个中文的`tooltip`。想要有的话就必须静态初始化所有的表情。</font>**这是个问题。

  * 读取了表情的qrc路径之后就可以直接添加到容器中

    ```c++
    void EmojiTableWidget::showEmoji(EmojiType type)
    {
        EmojiInfo emojiInfo = loadEmoji(type);
        qDebug() << emojiInfo.toString();
    
        int emojiRowCount = emojiInfo.getEmojiCount() / EmojiColCount;
        if(emojiInfo.getEmojiCount() % EmojiColCount)
        {
            emojiRowCount++;
        }
        this->setRowCount(emojiRowCount);
    
        // 添加表情
        int rowIndex = 0, colIndex = 0;
        const auto & emojiVec = emojiInfo.getEmojiVector();
        for(int i = 0; i < emojiVec.size(); i++)
        {
            rowIndex = i / EmojiColCount;
            colIndex = i % EmojiColCount;
            QLabel *emojiLabel = packageEmojiLabel(emojiVec.at(i));
            if(emojiLabel)
            {
                this->setCellWidget(rowIndex, colIndex, emojiLabel);
                this->setColumnWidth(colIndex,38);
                this->setRowHeight(rowIndex,38);
                emojiLabel->setUserData(rowIndex * EmojiColCount + colIndex,new StringUserData(emojiVec.at(i)));
            }
        }
    }
    ```

### （4）实现效果

![image-20210222153226741](C:\Users\ASUS\AppData\Roaming\Typora\typora-user-images\image-20210222153226741.png)

### （5）常用表情功能

![image-20210222153322377](C:\Users\ASUS\AppData\Roaming\Typora\typora-user-images\image-20210222153322377.png)

* 需要离线保存常用的表情

### （6）bugs

* 点击显示表情窗口的时候。点击一次按钮为显示，再点击一次还是一直显示，应该为关闭。

![image-20210222120500092](C:\Users\ASUS\AppData\Roaming\Typora\typora-user-images\image-20210222120500092.png)

* 点击窗口其他位置使表情窗口隐藏时，表情按钮会有一个悬浮样式

  ![image-20210222120628784](C:\Users\ASUS\AppData\Roaming\Typora\typora-user-images\image-20210222120628784.png)

## 2、消息展示模块

### （1）概要

由于整体的聊天消息列表使用的是`QListWidget`+`QListWidgetItem`和一些自定义的内容`QWidget`,自定义的`QWidget`包括下列几种：

```c++
ChatMessageItem  				// 展示聊天记录的基类
ChatMessageItemObject			// 展示文字和表情的item，位于消息列表左边
ChatMessageItemSelf				// 展示文字和表情的item，位于消息列表右边
ChatMessageImageItemObject		// 展示图片的item，位于消息列表左边	
ChatMessageImageItemSelf		// 展示图片的item，位于消息列表右边
```

### （2）选择的容器

容器选择的`QListWidget`,添加时使用一个`QListWidgetItem`,同时使用`QListWidgetItem`的`setItemWidget`函数设置其独特的`QWidget`。例如：

```c++
void ChatWidget::addMessageItem(QListWidget *listWidget, QPixmap &head,
                                const QString &message, bool isSelf)
{
    QListWidgetItem *item = new QListWidgetItem(listWidget);
    listWidget->addItem(item);
    zsj::ChatMessageData::ptr data(new zsj::ChatMessageData(head, message));
    QWidget *widget = nullptr;
    if(isSelf)
    {
        widget = new ChatMessageItemSelf(data, item, listWidget);
    }
    else
    {
        widget = new ChatMessageItemObject(data, item, listWidget);
    }
    listWidget->setItemWidget(item, widget);

    // 滚动到最底部
    listWidget->scrollToBottom();

}
```

### （3）实现方式

* 在添加item的时候需要判断显示聊天记录是显示在左边还是右边，显示在不同的位置设置的`QWidget`类是不同的。

* 显示的`QWidget`类目前只有三个子`widget`.一个`QLabel`用于展示头像，一个`QWidget`用于做布局容器，里面包含一个`QLabel`用于显示消息内容或者展示图片。

* 每个用于展示的`QWidget`类在`resize`时都会重新计算三个`widget`的位置，以便随着外部容器的变化而变化。同时`QWidget`内部的`QLabel`还会根据内容重新计算长度和宽度，自适应内容大小。

### （4）实现效果

![image-20210303091335328](C:\Users\ASUS\AppData\Roaming\Typora\typora-user-images\image-20210303091335328.png)

### （5）可以优化的地方

* 展示内容到消息列表左右两边的类有两个，实质上两个类中不同的地方只有`void adjustWidgetsPosition()override;`函数中内容不同。可以只使用一个类，使用一个标志位来指明显示的位置，即根据标志位来设置该函数体内的内容

## 3、聊天气泡功能

### （1）概要

* 由于聊天记录列表是用`QListWidget`+`QListWidgetItem`+`QWidget`做的，所以气泡的功能就在`QWidget`的子类中实现。主要需要显示气泡的是`QWidget`中的`QLabel`,所以`QLabel`需要自适应内容的大小。

* 当前聊天气泡`QLabel`支持显示`html2`的内容，所以可以用于直接显示markdown内容。

* 显示的时候是直接把消息输入框`QTextedit`的内容拿出来经过处理之后直接设置到`QLabel`里，所以`QLabel`的内容会带有`QTextEdit`文本的`html`内联样式，因为`QTextEdit`支持`html2`,而取出来的时候又是调用的`QTextedit`	的`toHtml`函数。

### （2）选择的容器

需要承载聊天记录（消息、表情和图片）的容器`QLabel`,气泡是设置在其外层的布局容器`QWidget`上的。

### （3）实现方式

* 气泡的样式当前是直接使用`QSS`,设置在内容容器`QLabel`的外部布局容器`QWidget`上

* 内容容器的宽高自适应

  * 宽度自适应

    观察输入的内容，根据内容中的`\n`来分段，然后使用`QFontMetrics`来获取内容的水平宽度。如下：

    ```c++
    QFont font = QFont("微软雅黑",18);
    QFont newFont(font.family(), font.pixelSize());
    QFontMetrics fm(newFont);
    QString testStr = "[测试字符]";
    int pixWidth = fm.horizontalAdvance(testStr);
    ```

    * 这样可以计算到每行的确定宽度，但是由于计算的字符串中含有`html`的一些标签，比如`<body><p></p>`等等，所以计算真实内容的时候需要减去这些标签的宽度，如果里面含有`<img>`标签则需要减去`<img>`的长度再加上一个表情的宽度才能得出真实长度。
    * 得出真实长度之后需要和当前行的最大宽度进行比较，大于当前最大值，小于当前消息列表的宽度减去一个偏移量，更新最大值。因为有时候消息内容少的时候，内容容器的长度不需要太大，同样内容太多的时候，内容容器的长度不能大于某一个值。

  * 高度自适应

    * 根据内容中的`\n`来分段，有多少个换行就使用当前`字体高度 * 换行个数`,如果当前行的内容宽度大于当前界面允许的最大宽度，则需要换行，依次增加一个换行的高度
    * 当内容的行数过于大的时候，高度自适应出现问题。会矮一些，所以在换行个数大于30的时候，增加一个修正高度`0.07 * 换行个数`

### （4）实现效果

![image-20210303091335328](C:\Users\ASUS\AppData\Roaming\Typora\typora-user-images\image-20210303091335328.png)

### （5）bugs

* 当输入的内容为英文符号时，自适应宽度会出现问题，会短一截，显示不全

![image-20210303094255422](C:\Users\ASUS\AppData\Roaming\Typora\typora-user-images\image-20210303094255422.png) 

第一个符号显示完全，第二个和第三个就有显示问题了。

## 4、聊天对象列表和聊天记录

