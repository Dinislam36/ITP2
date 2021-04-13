#include <iostream>
#include <iomanip>
using namespace std;


class fraction{
protected: int n;
protected: int x;
protected: int y;
public: fraction(){
    }
public: fraction(int n, int x, int y){
        this->n = n;
        this->x = x;
        this->y = y;
        normalize();
    }
    int sgn(int x){
        if(x>=0){
            return 1;
        } else{
            return -1;
        }
    }
    int getN(){ return n;}
    int getX(){ return x;}
    int getY(){ return y;}
    void normalize(){
        int n1 = abs(x);
        int n2 = abs(y);
        while(n1!= 0 && n2!= 0){
            if(n1>n2){
                n1 = n1%n2;
            } else{
                n2 = n2%n1;
            }
        }
        x = x/(n1+n2);
        y = y/(n1+n2);
        if(abs(x)>=y){
            n = n + x*sgn(n)/y;
            x = abs(x - (x/y)*y);
        }
    }

    friend istream& operator>>(istream& input, fraction& frac){
        string temp1;
        string t = "";
        bool b1 = false;
        bool b2 = false;
        input>>temp1;
        for(int i = 0; i < temp1.length();i++){
            if(temp1[i] == '.'){
                b1 = true;
            } else if(temp1[i] == '/'){
                b2 = true;
            }
        }

        if(b1 && !b2){
            double d = stod(temp1);
            frac = (fraction) d;
        } else if(!b1 && !b2){
            int i = stoi(temp1);
            frac = (fraction) i;
        } else if(!b1 && b2){
            for(int i = 0; i < temp1.length();i++){
                if(temp1[i] == '/'){
                    int i = stoi(t);
                    frac.x = i;
                    t = "";
                } else{
                    t = t + temp1[i];
                }
            }
            int i = stoi(t);
            frac.y = i;
            frac.n = 0;
        } else if(b1 && b2){
            for(int i = 0; i < temp1.length();i++){
                if(temp1[i] == '.'){
                    int i = stoi(t);
                    frac.n = i;
                    t = "";
                } else if(temp1[i] == '/'){
                    int i = stoi(t);
                    frac.x = i;
                    t = "";
                } else{
                    t = t + temp1[i];
                }
            }
            int i = stoi(t);
            frac.y = i;
        }
        frac.normalize();
        return input;
    }

    friend ostream& operator<<(ostream& output, fraction frac) {
        if (frac.n != 0) {
            output << frac.n;
            if(frac.x!= 0){
                cout<<".";
            }
        }
        if (frac.x != 0) {
            output <<frac.x << "/" << frac.y;
        }
        return output;
    }

    bool operator>(fraction& frac){
        return ((this->n*this->y + this->x*sgn(this->n))*frac.getY()>(frac.getN()*frac.getY()+frac.getX()*sgn(frac.getN()))*this->y);
    }

    bool operator<(fraction& frac){
        return ((this->n*this->y + this->x*sgn(this->n))*frac.getY()<(frac.getN()*frac.getY()+frac.getX()*sgn(frac.getN()))*this->y);
    }

    bool operator>=(fraction& frac){
        return ((this->n*this->y + this->x*sgn(this->n))*frac.getY()>=(frac.getN()*frac.getY()+frac.getX()*sgn(frac.getN()))*this->y);
    }

    bool operator<=(fraction& frac){
        return ((this->n*this->y + this->x*sgn(this->n))*frac.getY()<=(frac.getN()*frac.getY()+frac.getX()*sgn(frac.getN()))*this->y);
    }

    bool operator==(fraction& frac){
        return ((this->n*this->y + this->x*sgn(this->n))*frac.getY()==(frac.getN()*frac.getY()+frac.getX()*sgn(frac.getN()))*this->y);
    }

    bool operator!=(fraction& frac){
        return ((this->n*this->y + this->x*sgn(this->n))*frac.getY()!=(frac.getN()*frac.getY()+frac.getX()*sgn(frac.getN()))*this->y);
    }

    operator int(){
        return this->n;
    }

    operator double(){
        double x1 = (double) x;
        double y1 = (double) y;
        double n1 = (double) n;
        double t1 = (n1 + x1/y1)*100;
        int t = (int) t1;
        double out = t/100.0;
        return out;
    }

public: fraction(int i){
        this->n = i;
        this->x = 0;
        this->y = 1;
    }

public: fraction(double d){
        d = d*100;
        n = 0;
        x = (int) d;
        y = 100;
        normalize();
    }

    fraction& operator+(fraction& frac){
        this->x = (this->n*this->y + this->x*sgn(this->n))*frac.getY() + (frac.getN()*frac.getY() + frac.getX()*sgn(frac.getN()))*this->y;
        this->y = this->y*frac.getY();
        this->n = 0;
        normalize();
        return *this;
    }

    fraction& operator+(int& i){
        fraction temp = (fraction) i;
        *this = *this + temp;
        return *this;
    }

    fraction& operator+(double& i){
        fraction temp = (fraction) i;
        *this = *this + temp;
        return *this;
    }

    fraction& operator*(fraction& frac){
        this->x = (this->n*this->y+this->x*sgn(this->n))*(frac.getN()*frac.getY() + frac.getX()*sgn(frac.getN()));
        this->y = this->y*frac.getY();
        this->n = 0;
        this->normalize();
        return *this;
    }

    fraction& operator*(int& i){
        fraction temp = (fraction) i;
        *this = *this*temp;
        normalize();
        return *this;
    }

    fraction& operator*(double& i){
        fraction temp = (fraction) i;
        *this = *this*temp;
        return *this;
    }

    fraction& operator/(fraction& frac){
        this->x = (this->n*this->y+this->x*sgn(this->n))*frac.getY();
        this->y = this->y*(frac.getN()*frac.getY() + frac.getX()*sgn(frac.getN()));
        this->n = 0;
        normalize();
        return *this;
    }

    fraction& operator/(int& i){
        fraction temp = (fraction) i;
        *this = *this/temp;
        return *this;
    }

    fraction& operator/(double& i){
        fraction temp = (fraction) i;
        *this = *this/temp;
        return *this;
    }

    fraction& operator-(){
        if(n!= 0){
            n = -n;
        } else if(n == 0){
            x = -x;
        }
        normalize();
        return *this;
    }

    fraction& operator-(fraction& frac){
        fraction temp1 = -frac;
        return *this+temp1;
    }

    fraction&operator-(int& i){
        fraction temp = (fraction) i;
        *this = *this - i;
        return *this;
    }

    fraction&operator-(double& i){
        fraction temp = (fraction) i;
        *this = *this - i;
        return *this;
    }

};

template <class T>
class matrix{
protected: T** pointers;
protected: int n;
protected: int m;

public: matrix(int row, int column){
        pointers = new T*[row];
        for(int i = 0;i<row;i++){
            pointers[i] = new T[column];
        }
        n = row;
        m = column;
    }

    int absolute(int i){
        if(i > 0){
            return i;
        } else{
            return -i;
        }
    }

    void permutation(int row1, int row2){
        T* temp;
        temp = pointers[row1];
        pointers[row1] = pointers[row2];
        pointers[row2] = temp;
    }

    void elimination(int n1, int n2){
        double koef = pointers[n2][n1]/pointers[n1][n1];
        for(int i = 0; i < m;i++){
            pointers[n2][i] = pointers[n2][i] - koef*pointers[n1][i];
        }
    }

    int maximum(int column){
        int m = 0;
        int out = column;
        for(int i = column; i < n; i ++){
            if(absolute(pointers[i][column]) > m){
                m = absolute(pointers[i][column]);
                out = i;
            }
        }
        return out;
    }

    int getN(){
        return n;
    }

    int getM(){
        return m;
    }

    T get(int i, int k){
        return pointers[i][k];
    }

    void set(int i, int k, T value){
        pointers[i][k] = value;
    }


    friend istream& operator>>(istream &input, matrix& mat){
        for(int i = 0; i < mat.getN();i++){
            for(int k = 0; k < mat.getM();k++){
                input>>mat.pointers[i][k];
            }
        }
        return input;
    }

    friend ostream& operator<<(ostream &output, matrix& mat){
        for(int i = 0; i < mat.n;i++){
            for(int k = 0; k < mat.m;k++){
                output<<fixed<<setprecision(2)<<mat.pointers[i][k];
                if(k!=mat.m-1){
                    output<<" ";
                }
            }
            output<<endl;
        }
        return output;
    }

    matrix& operator=(matrix& mat){
        for(int i = 0; i < mat.getN(); i++){
            for(int k = 0;k < mat.getM();k++){
                this->pointers[i][k] = mat.get(i,k);
            }
        }
        return *this;
    }

    matrix& operator+(matrix& mat){
        matrix<T>* temp = new matrix<T>(this->n,this->m);
        for(int i = 0;i<mat.getN();i++){
            for(int k = 0;k < mat.getM();k++){
                T d = mat.get(i,k);
                temp->pointers[i][k] = this->pointers[i][k] + d;
            }
        }
        return *temp;
    }

    matrix& operator-(matrix& mat){
        for(int i = 0;i<mat.getN();i++){
            for(int k = 0;k < mat.getM();k++){
                T d = mat.get(i,k);
                this->pointers[i][k] = this->pointers[i][k] - d;
            }
        }
        return *this;
    }

    matrix& operator*(matrix& mat){
        T value;
        matrix<T>* temp = new matrix<T>(this->n,mat.getM());
        for(int i = 0;i < this->n;i++){
            for(int k = 0;k < mat.getM();k++){
                value = (T) 0;
                for(int j = 0; j <this->m; j++){
                    T d = mat.get(j,k);
                    T d1 = this->pointers[i][j];
                    value = value + d1*d;
                }
                temp->set(i,k,value);
            }
        }
        return *temp;
    }

    matrix transpose(){
        matrix temp(this->m,this->n);
        for(int i = 0;i<this->m;i++){
            for(int k = 0;k<this->n;k++){
                temp.set(i,k,this->pointers[k][i]);
            }
        }
        return temp;
    }

};


int main() {
    int n,m;
    cin>>n>>m;
    matrix<double> D1(n,m);
    cin>>D1;
    cin>>n>>m;
    matrix<double> D2(n,m);
    cin>>D2;
    matrix<double> D3 = D1+D2;
    cin>>n>>m;
    matrix<fraction> A(n,m);
    cin>>A;
    cin>>n>>m;
    matrix<fraction> B(n,m);
    cin>>B;
    matrix<fraction> g = A*B;
    cout<<D3;
    cout<<g;
    return 0;
}
