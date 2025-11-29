#include<iostream>
#include<string>
#include<cstring>

using namespace std;

class Polynomial
{
    protected:
    int a[100];
    int asize;
    char x='x';
    int exp[100];
    int expsize;
    public:
    ~Polynomial()
    {
        cout<<"Object Destroyed"<<endl;
    }
    Polynomial()
    {
        asize=0;
        expsize=0;
        for(int i=0;i<99;i++)
        {
            a[i]=0;
            exp[0]=0;
        }
    }
    Polynomial(int _a,int _x)
    {
        a[0]=_a;
        exp[0]=_x;
    }
    void addTerm(int coefficient,int power)
    {
        if(asize>=100 || expsize>=100)
        {
            throw"Insufficient Memory";
        }
        else
        {
            a[asize]=coefficient;
            asize++;
            exp[expsize]=power;
            expsize++;
        }
    }
    int getDegree()
    {
        int max=0;
        for(int i=0;i<this->expsize;i++)
        {
            if(this->exp[i]>max)
            {
                max=exp[i];
            }
        }
        return max;
    }
    int getCoefficient(int pow)
    {
            for(int i=0;i<expsize;i++)
            {
                if(exp[i]==pow)
                {
                    return a[i];
                }
            }               
    }
    
    Polynomial operator=(Polynomial other)
    {
        for(int i=0;i<100;i++)
        {
            this->a[i]=other.a[i];
        }
        for(int i=0;i<100;i++)
        {
            this->exp[i]=other.exp[i];
        }
        this->asize=other.asize;
        this->expsize=other.expsize;

        return *this;
    }
    Polynomial operator+(Polynomial rhs)
    {
        Polynomial neww;
        for(int i=0;i<100;i++)
        {
            if(this->exp[i]==rhs.exp[i])
            {
                neww.a[i]=this->a[i]+rhs.a[i];
                neww.exp[i]=this->exp[i];
            }
            else
            {
                neww.a[i]=this->a[i];
                neww.exp[i]=this->exp[i];
                neww.a[i]=rhs.a[i];
                neww.exp[i]=rhs.exp[i];
            }
        }
    }
    Polynomial derrivative(void)
    {
        Polynomial neww;
        for(int i=0;i<100;i++)
        {
            neww.a[i]=this->exp[i]*this->a[i];
            neww.exp[i]=this->exp[i]-1;
        }
        return neww;
    }    
    Polynomial antiDerrivative(void)
    {
        Polynomial neww;
        for(int i=0;i<100;i++)
        {
            neww.a[i]=this->a[i]/(this->exp[i]+1);
            neww.exp[i]=this->exp[i]+1;
        }
        return neww;
    }
    void clear()
    {
        for(int i=0;i<100;i++)
        {
            this->a[i]=0;
        }
    }
    Polynomial operator-(Polynomial rhs)
    {
        Polynomial neww;
        for(int i=0;i<100;i++)
        {
            if(this->exp[i]==rhs.exp[i])
            {
                neww.a[i]=this->a[i]-rhs.a[i];
                neww.exp[i]=this->exp[i];
            }
            else
            {
                neww.a[i]=this->a[i];
                neww.exp[i]=this->exp[i];
                neww.a[i+1]=rhs.a[i+1];
                neww.exp[i+1]=rhs.exp[i+1];
            }
        }
    }
   
    ostream& operator<<(const Polynomial &p) 
    {
        for(int i=0;i<100;i++)
        {
            if(p.a[i]>0)
            {    
                cout<<'+'<<p.a[i]<<'x'<<'^'<<p.exp[i];
            }
            else if(p.a[i]<0)
            {
                cout<<p.a[i]<<'x'<<'^'<<p.exp[i];
            }
            else if(p.a[i]==0)
            {
                cout<<'+'<<p.a[i]<<'x'<<'^'<<p.exp[i];
            }
        }
        return cout;
    }
};

int main()
{
    Polynomial p1(8,4);
    p1.addTerm(7,3);
    p1.addTerm(6,2);
    p1.addTerm(5,1);
    int d=p1.getDegree();
    cout<<"Degree:"<<d<<endl;
    cout<<"Coefficient:"<<p1.getCoefficient(2)<<endl;
    
    Polynomial p2(5,3);
    p2.addTerm(4,2);
    p2.addTerm(3,1);
    p2.addTerm(2,1);
    
    Polynomial p3(p2);
    cout<<"Polynomial 3:"<<p3<<endl;
    Polynomial P4=p2+p3;
    return 0;
}