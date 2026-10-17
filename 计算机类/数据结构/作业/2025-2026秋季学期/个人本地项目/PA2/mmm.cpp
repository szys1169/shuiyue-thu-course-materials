#include <iostream>

using namespace std;

//ʹ�����ڵ���������Ϣ
//��������ʹ��һ����������������SectNode
class SectNode{
public:
    int childNum; //ͽ�ܸ���
    int* child; //����ͽ�ܣ��������ͽ�ܵ����
    int mainChild = 0; //��ͳͽ�ܣ�0��ʾû����ͳ����
    int master = 0;  //ʦ���ı��
    bool hasMainMaster = false; //�Ƿ�����ͳʦ����������ʦ����ֱ�Ӹ���ʼֵ0
    long long power;  //����ֵ
    long long powerOfChildren = 0; //�Ա��ڵ�Ϊ���ڵ������������ֵ֮��
    int director = -1; //��·�߱��
    
};

void culPowerOfChildren(SectNode* s, int n){
    //����һ�Ÿ������������������n���ڵ��Ӧ������������ֵ��

    if(s[n].childNum == 0){
        s[n].powerOfChildren = s[n].power;
        return;
    }else{
        for(int i=0; i<s[n].childNum; i++){
            culPowerOfChildren(s, s[n].child[i]);
            s[n].powerOfChildren += s[s[n].child[i]].powerOfChildren;
        }
        s[n].powerOfChildren += s[n].power;
    }
}

//���
void show(SectNode* s, int length){
    for(int i=1; i<=length; i++){
        cout << s[i].director << endl;
    }
}

void guide(SectNode* s, int length)
{

}

int main(){
    int N;
    cin >> N;  //�ڵ�����
    SectNode* Sect = new SectNode[N+1]; 

    //����
    for(int i=1; i<=N; i++){
        int n_i; //��ӦSect[i]�ڵ���ӽڵ���Ŀ
        cin >> n_i;  
        if(n_i == 0){
            Sect[i].childNum = 0;
            Sect[i].child = nullptr;
        }else{
            Sect[i].childNum = n_i;
            Sect[i].child = new int[n_i];
            for(int j=0; j<n_i; j++){
                cin >> Sect[i].child[j];
                Sect[Sect[i].child[j]].master = i;  //�����ӽڵ�ĸ��ڵ���Ϊ���i
            }
        }
    }
    for(int i=1; i<=N; i++){
        //��������ֵ
        cin >> Sect[i].power;
    }
    //���벿���Ѿ�����û����

    //����ÿһ���ڵ��������
    culPowerOfChildren(Sect, 1);

    //����ÿ�������ͳͽ��
    for(int i=1; i<= N; i++){
        if(Sect[i].childNum == 0){
            continue;
        }
        int max = Sect[i].child[0];
        for(int j=0; j<Sect[i].childNum; j++){
            if(Sect[Sect[i].child[j]].powerOfChildren > Sect[max].powerOfChildren){
                max = Sect[i].child[j];
            }
            if(Sect[Sect[i].child[j]].powerOfChildren == Sect[max].powerOfChildren){
                if(Sect[i].child[j] < max){
                    max = Sect[i].child[j];
                }
            }
        }
        Sect[max].hasMainMaster = true;
        Sect[i].mainChild = max;
    }

    //Ϊÿ���������·�ߵ�ֵ��director��ֵ��
    guide(Sect, N);
    for(int i=2; i<=N; i++){
        //ֻ��2�ŵ㿪ʼ���㣬1�ŵ����·�߾��ǳ�ʼֵ-1
        if(Sect[i].hasMainMaster == false){
            //û����ͳʦ����Ҳ���ǲ���ĳ�������ͳ���ӡ����û����·��
            continue;
        }else{
            //ʦ������ͳʦ��
            if(Sect[Sect[i].master].director == -1){
                //���������ʦ��û����·�ߣ������ֻ��Ҫ����ʦ����
                if(Sect[i].power < Sect[Sect[i].master].power){
                    Sect[i].director = Sect[i].master;
                }else{
                    continue;
                }
            }else{
                //���������ʦ������·�ߣ���һֱ���ϱȽϺ���·�ߵĴ�С
                int thisDirector = Sect[i].master;  //��ʼֵ��������ʦ��
                while(thisDirector != -1 && Sect[i].power > Sect[thisDirector].power){
                    thisDirector = Sect[thisDirector].director;
                }
                Sect[i].director = thisDirector;
                
            }
        }
    }

    show(Sect, N);

    for (int i=1; i<=N; i++) {
        if (Sect[i].child != nullptr) {
            delete[] Sect[i].child;
        }
    }
    delete[] Sect;
    return 0;
}
/*
������
13
3 2 3 4
3 5 6 7
1 8
4 10 11 12 13
0
0
0
1 9
0
0
0
0
0
13 12 11 10 9 8 7 6 5 4 3 2 1

6
1 2
1 3
1 4
1 5
1 6
0
1 4 6 2 3 5*/