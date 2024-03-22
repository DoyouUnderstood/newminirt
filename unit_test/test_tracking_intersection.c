#include <criterion/criterion.h>
#include "../include/shape.h"

Test(intersection_tests, intersect_sets_object_on_the_intersection) 
{
    t_ray ray = {point(0, 0, -5), vector(0, 0, 1)};
    t_object sphere_object;
    t_sphere sphere = sphere_create();
    sphere_object.type = SPHERE;
    sphere_object.obj = &sphere;

    int count;
    t_intersection* xs = intersect(&ray, &sphere_object, &count);

    cr_expect_eq(count, 2, "Expected 2 intersections, but got %d", count);
    for (int i = 0; i < count; i++) {
        cr_expect(xs[i].object == &sphere_object, "Expected object to be the sphere object");
    }
    free(xs);
}

Test(intersection_tests, encapsulates_t_and_object) {
    t_sphere s = sphere_create();
    t_object sphere_object;
    sphere_object.type = SPHERE;
    sphere_object.obj = &s;

    int count;
    t_intersection* intersections = intersect(&(t_ray){.origin = point(0,0,-5), .direction = vector(0,0,1)}, &sphere_object, &count);
    
    if (count > 0) {
        cr_expect_float_eq(intersections[0].t, 4.0, 1e-6, "Expected t to be 4.0, was %f", intersections[0].t);
        cr_expect(intersections[0].object == &sphere_object, "Intersection object does not match the given sphere object");
    } else {
        cr_expect_fail("No intersections found");
    }

    free(intersections);
}
