/*DSA*/#include "simu.h"

void simu( int winds, int duration ) { //窗口数、服务时长
   Queue<int>* wind = new Queue<int>[winds]; //窗口各维护一个队列，记录顾客们的服务时长
   while ( duration-- ) { //在下班之前，每隔一个单位时间
      for ( int i = 0; i < winds; i++ ) //各非空队列的队首顾客接受
         if ( ! wind[i].empty() && ( 1 > wind[i].front()-- ) ) //单位时长的服务
            wind[i].dequeue(); //服务完毕则出列，后继者接替
      if ( rand() % ( 1 + winds ) ) //新顾客以wins/(wins + 1)的概率到达
         wind[ rand()%winds ].enqueue( 1 + rand()%99 ); //随机选窗口、定时长
      /*DSA*/displayProgress( wind, winds, duration ); //显示当前各（窗口）队列情况
      /*DSA*/delay > 0 ? //若命令行指定的时间间隔为正数
      /*DSA*/  _sleep( delay ) : //则做相应的延迟
      /*DSA*/  getchar(); //否则，以手动方式单步演示
   } //for
   delete [] wind; //释放所有队列
} //simu
