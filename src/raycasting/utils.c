#include "cub3d.h"
#include "raycasting.h"

double	normalize_angle(double angle)
{
    // angle = fmodf(angle, 2 * M_PI);
    // if (angle < 0)
    //     angle += 2 * M_PI;
    if (angle < 0)
        angle += (2 * M_PI);
    if (angle > (2 * M_PI))
        angle -= (2 * M_PI);
    return (angle);
}
