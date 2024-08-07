// Пока не используется (в коде дублируется)
/*
#include "processimitation.h"



ProcessImitation::ProcessImitation()
{
    QVector<double> x(1601), y(1601);
    y[0] = 0;
    x[0] = -800;

    for (int i=1; i<1601; ++i)
    {
        x[i] = i - 800;
        std::default_random_engine generator(time(0));
        std::normal_distribution<double> distribution(0.0, 1.0);

        y[i] = y[i-1] + distribution(generator);
    }

}
*/
