#include <iostream>
#include <queue>
#include <string>
using namespace std;

class Pcb
{
public:
    string name;
    char status;
    int memory;
    Pcb(string n, char s, int m)
    {
        name = n;
        status = s;
        memory = m;
    }
};
queue<Pcb *> pCreat, pReady, pRunning, pBlocked, pRelese;
int mAll, mCreat, mReady, mRunning, mSum = 0;

void output(queue<Pcb *> toOutq)
{
    queue<Pcb *> outq = toOutq;
    while (!outq.empty())
    {
        cout << outq.front()->name << "|";
        outq.pop();
    }
    cout << endl;
}

void outputAll()
{
    cout << "Creat:";
    output(pCreat);
    cout << "Ready:";
    output(pReady);
    cout << "Running:";
    output(pRunning);
    cout << "Blocked:";
    output(pBlocked);
    cout << "Release:";
    output(pRelese);
}

bool dispatch()
{
    if (pReady.empty())
    {
        cout << "Ready has no pcb!";
    }
    else
    {
        pRunning.push(pReady.front());
        pReady.pop();
    }
    return true;
}

bool creatPcb()
{
    string n;
    int m;
    cout << "Please input process (name memory):";
    cin >> n >> m;
    Pcb *p = new Pcb(n, 'C', m);
    if (mSum + m <= mAll)
    {
        pReady.push(p);
    }
    else
    {
        pCreat.push(p);
    }
    return true;
}

bool ioReq()
{
    if (pRunning.empty())
    {
        cout << "Running has no process!" << endl;
    }
    else
    {
        pBlocked.push(pRunning.front());
        pRunning.pop();
        dispatch();
    }
    return true;
}

bool timeout()
{
    if (pRunning.empty())
    {
        cout << "Running has no process!" << endl;
    }
    else
    {
        pReady.push(pRunning.front());
        pRunning.pop();
        dispatch();
    }
    return true;
}

bool ioFinish()
{
    if (pBlocked.empty())
    {
        cout << "Blocked has no process!" << endl;
    }
    else
    {
        pReady.push(pBlocked.front());
        pBlocked.pop();
    }

    return true;
}

bool release()
{
    if (pRunning.empty())
    {
        cout << "Running has no process!" << endl;
    }
    else
    {
        pRelese.push(pRunning.front());
        mSum -= pRunning.front()->memory;
        pRunning.pop();
        dispatch();
        if (!pCreat.empty() && mSum + pCreat.front()->memory <= mAll)
        {
            pReady.push(pCreat.front());
            pCreat.pop();
        }
    }
    return true;
}

int main()
{
    /*初始化进程*/
    int pNum;
    cout << "Please input num of processes:";
    cin >> pNum;
    cout << "Please input memory:";
    cin >> mAll;
    int a = 2;
    while (pNum--)
    {
        string n;
        char s;
        int m;
        cout << "Please input every process (name status memory):";
        cin >> n >> s >> m;
        Pcb *p = new Pcb(n, s, m);
        mSum += m;
        //cout<<p->name;
        switch (s)
        {
        case 'R':
        {
            pReady.push(p);
            break;
        }
        case 'B':
        {
            pBlocked.push(p);
            break;
        }
        case 'U':
        {
            pRunning.push(p);
            break;
        }
        default:
        {
            cout << "ERROR";
            break;
        }
        }
    }
    outputAll();
    //cout << pReady.front()->name << endl;

    int order;
    while (cin >> order)
    {
        switch (order)
        {
        //Creat a Process
        case 1:
        {
            creatPcb();
            break;
        }
        //IO Request
        case 2:
        {
            ioReq();
            break;
        }
        //IO Finish
        case 3:
        {
            ioFinish();
            break;
        }
        // Timeout
        case 4:
        {
            timeout();
            break;
        }
        //Release
        case 5:
        {
            release();
            break;
        }
        default:
            break;
        }
        outputAll();
    }
    return 0;
}
