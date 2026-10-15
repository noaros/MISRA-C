/* Dir 4.10 BAD: no include guard, so including this twice redefines
 * struct sensor_reading and breaks the build. */
struct sensor_reading
{
    unsigned int raw;
};
