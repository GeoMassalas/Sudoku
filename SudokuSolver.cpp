#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <fstream>

using namespace std;

class Board{

private:
    class Number{

    private:
        int num;
        vector<int> pos_values;
    public:

        Number(){};

        void init(int row, int col, int num)
        {
            this->num = num;
            if(num == 0)
            {
                for(int i = 1; i < 10; i++)
                    pos_values.push_back(i);
            }
        }

        int getNum()
        {
            return num;
        }

        vector<int> getPossibleValues()
        {
            return pos_values;
        }

        void removePosValue(int x)
        {
            pos_values.erase(remove(pos_values.begin(), pos_values.end(), x), pos_values.end());
        }

        void setToValue()
        {
            if(pos_values.size() == 1)
                num = pos_values[0];
        };
    };

    Number nums[9][9];
    bool solved;

public:
    Board(int *board[9])
    {
        solved = false;
        for(int i = 0; i < 9; i++)
        {
            for(int j = 0; j < 9; j++)
            {
                nums[i][j].init(i, j, board[i][j]);
            }
        }
    }

    bool checkIfSovled()
    {
        int count = 0;
        for(int i = 0; i < 9; i++)
        {
            for(int j = 0; j < 9; j++)
            {
                if(nums[i][j].getNum() == 0)
                    count++;
            }
        }
        if(count == 0)
            return true;
        else
            return false;
        
    }

    void Solve()
    {
        for(int i=0; i < 9; i++)
        {
            for(int j=0; j < 9; j++)
            {
                if(nums[i][j].getNum() == 0)
                {
                    vector<int> p = nums[i][j].getPossibleValues();
                    for(std::vector<int>::iterator it = p.begin(); it != p.end(); ++it)
                    { 
                            if(checkRow(j,*it) || checkCol(i,*it) || checkBox(*it,i,j))
                                nums[i][j].removePosValue(*it);
                    }
                }
            }
        }
        this->updateNumbers();
    }

    bool checkRow(int row, int num)
    {
        for(int i = 0; i < 9; i++)
        {
            if(nums[i][row].getNum() == num)
                return true;
        } 
        return false;
    }

    bool checkCol(int col, int num)
    {
        for(int i = 0; i < 9; i++)
        {
            if(nums[col][i].getNum() == num)
                return true;
        } 
        return false;
    }

    bool checkBox(int num, int row, int col)
    {
        int r,c;
        if(row < 3)
            r = 0;
        else if(row < 6)
            r = 3;
        else
            r = 6;
        if(col < 3)
            c = 0;
        else if(col < 6)
            c = 3;
        else
            c = 6;
        
        for(int i = r; i < r + 3; i++)
        {
            for(int j = c; j < c + 3; j++)
            {
                if(nums[i][j].getNum() == num)
                {
                    return true;
                }
            }
        }
        return false;
    }

    void printCurrentState()
    {
        cout << "---------------------" << endl;
        for(int i=0; i <9; i++){
            for(int j=0; j <9; j++){
                cout << nums[i][j].getNum() << " ";
            }
            cout << endl;
        }
    }

    void updateNumbers()
    {
        for(int i = 0; i < 9; i++)
        {
            for(int j = 0; j < 9; j++)
            {
                nums[i][j].setToValue();
            }
        }
    }
};

int main(){
    int *board[9];
    for(int i = 0; i < 9; i++)
        board[i] = new int[9];
    ifstream myfile("example1.txt");
    string s;
    if (myfile.is_open())
    {
        for(int i=0; i < 9; i++){
            getline(myfile,s);
            for(int j = 0; j < 9; ++j) {
                board[i][j] = s[j]-48;
            }
        }
        myfile.close();
        Board b(board);
        while(!b.checkIfSovled())
        {
            b.Solve();
            b.printCurrentState();
        }
    }else 
        cout << "Unable to open file" << endl; 
    return 0;
}