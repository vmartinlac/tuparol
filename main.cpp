#include <iostream>
#include <random>

class Universe
{
public:

    virtual bool isTerminal(int state) = 0;
    virtual int getNumStates() = 0;
    virtual int getNumActions() = 0;
    virtual void sampleTransition(int state_from, int action, int& state_to, double& reward) = 0;
    //virtual double getTransitionProbability(int state_from, int action, int state_to) = 0;
    //virtual void getRewardProbability(int state_from, int action, int state_to, double& mu, double& sigma) = 0;
};

class UniverseImpl : public Universe
{
public:

    UniverseImpl()
    {
        myGrid =
            "                La  "
            "                L  b"
            "    a           LLLL"
            "                    "
            "           b        "
            "                  b "
            "                    "
            "    a LLLL LL LL  LL"
            "        L           "
            "        L           "
            "           a        "
            "   b    L           "
            "        L           "
            "        LLLLLL      "
            "         LL         "
            "          a         "
            "          L         "
            "        bLLL        "
            "    LLLLLL          "
            "        WL         W";
    }

    bool isTerminal(int state) override
    {
        return (state == N*N);
    }

    int getNumStates() override
    {
        return N*N+1;
    }

    int getNumActions() override
    {
        return 4;
    }

    void sampleTransition(int state_from, int action, int& state_to, double& reward) override
    {
        if(state_from == N*N)
        {
            state_to = N*N;
            reward = 0.0f;
        }
        else if(myGrid[state_from] == 'W')
        {
            state_to = N*N;
            reward = 1.0f;
        }
        else if(myGrid[state_from] == 'L')
        {
            state_to = N*N;
            reward = -1.0f;
        }
        else
        {
            if(action == 0)
            {
                state_to = state_from - N;
                if(state_to < 0)
                {
                    state_to = N*N;
                    reward = -1.0f;
                }
            }
            else if(action == 1)
            {
                state_to = state_from+1;
                if(state_to/N != state_from/N)
                {
                    state_to = N*N;
                    reward = -1.0f;
                }
            }
            else if(action == 2)
            {
                state_to = state_from + N;
                if(state_to >= N*N)
                {
                    state_to = N*N;
                    reward = -1.0f;
                }
            }
            else if(action == 3)
            {
                state_to = state_from-1;
                if(state_to/N != state_from/N)
                {
                    state_to = N*N;
                    reward = -1.0f;
                }
            }

            if(state_to < N*N)
            {
                if(myGrid[state_to] != ' ')
                {
                    int available[N*N];
                    int count = 0;
                    for(int i=0; i<N*N; i++)
                    {
                        if(myGrid[i] == myGrid[state_to])
                        {
                            available[count] = i;
                            count++;
                        }
                    }

                    state_to = available[ myRandom()%count ];
                }
            }
        }
    }

protected:

    const char* myGrid;
    static constexpr int N = 20;
    std::default_random_engine myRandom;
};


int main(int num_args, char** args)
{
    UniverseImpl universe;

    const int NS = universe.getNumStates();
    const int NA = universe.getNumActions();

    std::vector<float> action_values(NA*NS, 0.0f);

    bool go_on = true;
    while(go_on)
    {
    }

    return 0;
}

