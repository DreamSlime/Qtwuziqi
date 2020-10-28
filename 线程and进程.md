线程and进程

并发：多个时间在同一时间段内发生。有交替的意思。A->B->A

并行：指多个事件在同一时刻发生。同时

进程：一个内存中运行的应用程序

内存：所有的应用程序都需要进入到内存中执行，临时存储RAM

硬盘：永久储存ROM

点击应用程序执行，进入到内存中占用一些内存执行进入到内存的程序叫进程、

cpu：中央处理器 对数据进行计算，指挥电脑中软件和硬件干活

cpu的分类：

AMD，Inter Inter Core(核心) i7 8866   4核心8线程

8线程：同时执行8个任务

''''''

点击功能（病毒查杀，垃圾清理，电脑加速）执行

就会开启一条应用程序到cpu的执行路径，cpu就可以通过这个路径执行功能，这个路径就叫线程。

线程属于进程，是进程中的一个执行单元，负责程序的执行

单核心单线程cpu：cpu在多个线程之间做高速 的切换，轮流执行多个线程，效率低，切换速度1/n秒

4核心8线程：有8个线程，可以同时执行8个线程，8个线程在多个任务之间做高速的切换，速度是单线程cpu的8倍（每个任务执行到的几率都被提高了8倍）

多线程的好处：效率高，且多个线程之间不会相互影响



线程调度：

分时调度：平均分配每个线程占用CPU的时间

抢占式调度：优先让优先级高的线程使用CPU。如果线程优先级相同则随机（线程的随机性）

实际上，CPU（中央处理器）使用抢占式调度模式在多个线程间进行高速的切换，对于CPU的一个核而已，某一时刻，只能执行一个线程，而CPU的在多个线程间切换速度相对于我们打包感觉要快得多，看上去就是同一时刻运行的。

多线程程序并不能提升程序的运行速度，但是能够把提高程序运行效率，让CPU的使用率更高。

JVM执行main方法，main方法会进入到栈内存                                           JVM会找操作系统开辟一条main方法通向cpu的执行路径                         cpu就可以通过这个路径来执行我们的main方法。                                      而这个路径有一个名字叫main(主)线程                                                                        

![1599310988442](C:\Users\slime\AppData\Roaming\Typora\typora-user-images\1599310988442.png)

获取线程的名称：

1.使用Thread类中的方法getName()

String getName()返回线程的名称

2.可以先获取到当前正在执行的线程，使用线程中的方法getName()获取线程的名称

static thread currentThread() 返回对当前正在执行的线程对象的引用。

```java
System.out.println(Thread.currentThread().getName());
```

线程的名称：

主线程：main

新线程：Thread-0,Thread-1,Thread-2...

设置线程的名称：

1.使用Thread类中的方法setname(名称)

void setName(String name) 改变线程 名称，使之与name相同

2.创建一个带参数的构造方法，参数传递线程的名称；调用父类的带参构方法，把线程的名称传递给父类，让父类（Thread）给子线程起一个名字

Thread(String name)分配新的Thread对象

```java
public  MyThread(String name){    super(name);}
```



public static void sleep(long mills)使当前正在执行的线程以指定的毫秒数暂停（暂时停止执行）

毫秒数结束之后，线程继续执行

创建多线程的第二种方法：实现runnable接口

java.lang.Runnable

Runnable 接口应该由那些打算通过某些线程执行其实例来实现，类必须定义位一个run的无参数方法

构造方法：

Thread(Runnable target)配分新的Thread对象

Thread(Runnable target,String name)

实现步骤：

1.创建一个Runnable 接口的实现类

2.在实现类中重写Runnable接口的run方法，设置线程任务

3.创建要给Runnable接口的实现类对象

4.创建Thread类对象，构造方法中传递runnable接口的实现类对象

5.调用Thread类中的start方法，开启新线程执行run方法



实现Runnable接口创建多线程程序的好处：

1.避免了单继承的局限性

一个类只能继承一个类（一个人只能有一个亲爹），类继承了Thread类就不能继承其他的类

实现了Runnable接口，还可以继承其他的类，实现其他的接口

2.增强了程序的扩展性，降低了程序的耦合性（解耦）

实现Runnable接口的方式，把设置线程的任务和开启线程的任务进行了分离（解耦）

实现类中，重写了run方法用来设置线程任务

创建Thread类对象，调用start方法：用来开启新的线程



匿名内部类实现多线程的创建

匿名：没有名字

内部类：写在其他类内部的类

匿名内部类作用：简化代码

把子类继承父类，重写父类的方法，创建子类对象合一步完成

把实现类实现接口，重写接口中的方法，创建实现类对象合成一步完成

匿名内部类的最终产物：子类/实现类对象，而这个类没有名字

格式

​	new 父类/接口(){	

​		重复父类/接口中的方法

}

```java
new Thread(){
            @Override
            public void run() {
                for (int i = 0; i < 20; i++) {
                    System.out.println(Thread.currentThread().getName()+i);
                }
            }
        }.start();
```

```java
new Thread (new Runnable(){
            @Override
            public void run() {
                for (int i = 0; i <20 ; i++) {
                    System.out.println(Thread.currentThread().getName()+i);
                }
            }
        }).start();
```

多线程访问了共享的数据，会产生线程安全问题

#### 线程同步

要解决多线程并发访问一个资源的安全性问题，java提供了同步机制（Synchronized）来解决。

三种方法完成同步操作：

1.同步代码块

2.同步方法

3.锁机制

##### 同步代码块

同步代码块：synchronized关键字可以用于方法中的某个区块中，表示只对这个区块的资源实行互斥访问。

格式：

```
synchronized(同步锁){
	需要同步操作的代码
}
```

同步锁：

对象同步锁只是一个概念，可以想象为在对象上标记一个锁

1.锁对象 可以是任意类型

2.多个线程对象，要使用同一把锁

注意：在任何时候，最多允许一个线程拥有同步锁，谁拿到锁就进入代码块，其他线程的只能在外等着（BLOCKED）。

同步技术的原理：

使用了一个锁对象，这个锁对象叫同步锁，也叫对象监视器

3个线程一起抢夺cpu的执行权，谁先抢到了执行run方法进行卖票，t0抢到了cpu的执行权，执行run方法，遇到synchronized代码块，这时t0会检查synchronized代码块中是否有锁对象，发现有，就会获取到锁对象，进入到同步中执行。

，t1抢到了cpu的执行权，执行run方法，遇到synchronized代码块，这时t1会检查synchronized代码块中是否有锁对象，发现没有，t1就会进入到阻塞状态，会一直等待t0线程归还锁对象，一直到t0线程执行完全同步中的代码，会把锁对象归还给同步代码块，这时候t1次啊能获得锁对象，进入到同步中执行。

总结：

同步中的线程，没有执行完毕不会释放锁，同步外的线程没有锁进不去同步。

同步保证了只能有一个线程子在同步中执行共享数据

保证了安全

程序频繁的判断锁，释放锁，程序的效率会降低

##### 同步代码块

同步代码块：synchronized关键字可以用于方法中的某个区块中，表示只对这个区块的资源实行互斥访问。

格式：

```
public synchronized void method{
	可能会产生线程安全问题的代码
}
```

同步锁是谁？

对于非static方法，同步锁就是this

对于static方法，我们使用当前方法所在类的字节码对象(类名.class)

静态方法的锁对象不能是this，this是创建对象之后产生的，静态方法优先于对象

静态方法的锁对象是本类的class属性。

#### Lock锁

java.util.concurrent.locks.Lock接口

Lock实现提供了比使用synchronized方法和语句可获得的更广泛的锁定操作。

Lock接口中的方法：

void lock();获取锁

void unlock();释放锁

java.util.concurrent.locks.ReentrantLock implements locks接口

使用步骤：

1.    在成员位置创建一个ReentrantLock对象
2. 在可能会出现安全问题的代码前调用Lock接口中的方法lock获取锁
3. 在可能会出现安全问题的代码后调用lock接口中的方法unlock释放锁。

#### 线程状态

![1600432379201](C:\Users\slime\AppData\Roaming\Typora\typora-user-images\1600432379201.png)

