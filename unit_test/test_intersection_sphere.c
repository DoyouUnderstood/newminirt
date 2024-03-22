#include <criterion/criterion.h>
#include "../include/shape.h"

Test(sphere_intersections, ray_intersects_sphere_at_two_points) {
    t_ray ray = {point(0, 0, -5), vector(0, 0, 1)};
    t_sphere sphere = sphere_create();
    
    t_object obj;
    obj.type = SPHERE;
    obj.obj = &sphere;

    int count;
    t_intersection* xs = sphere_intersect(&ray, &obj, &count);

    cr_expect_eq(count, 2, "Expected 2 intersections, got %d", count);
    cr_expect_float_eq(xs[0].t, 4.0, 1e-6, "First intersection point was %f, expected 4.0", xs[0].t);
    cr_expect_float_eq(xs[1].t, 6.0, 1e-6, "Second intersection point was %f, expected 6.0", xs[1].t);
    free(xs);
}


Test(sphere_intersections, ray_intersects_sphere_selon_une_tangente) {
    t_ray ray = {point(0, 1, -5), vector(0, 0, 1)};
    t_sphere sphere = sphere_create();
    t_object obj;
    obj.type = SPHERE;
    obj.obj = &sphere;
    int count;
    t_intersection* xs = sphere_intersect(&ray, &obj, &count);


    cr_expect_eq(count, 2, "Expected 2 intersections, got %d", count);
    cr_expect_float_eq(xs[0].t, 5.0, 1e-6, "First intersection point was %f, expected 5.0", xs[0].t);
    cr_expect_float_eq(xs[1].t, 5.0, 1e-6, "Second intersection point was %f, expected 5.0", xs[1].t);

    free(xs);
}


Test(sphere_intersections, ray_intersects_sphere_at_nothin_he_miss) {
    t_ray ray = {point(0, 2, -5), vector(0, 0, 1)};
    t_sphere sphere = sphere_create();
    t_object obj;
    obj.type = SPHERE;
    obj.obj = &sphere;

    int count;
    t_intersection* xs = sphere_intersect(&ray, &obj, &count);

    cr_expect_eq(count, 0, "Expected 0 intersections, got %d", count);

    free(xs);
}

Test(sphere_intersections, ray_rayon_prend_naissance_à_l_intérieur_d_une_sphère) {
    t_ray ray = {point(0, 0, 0), vector(0, 0, 1)};
    t_sphere sphere = sphere_create();
    t_object obj;
    obj.type = SPHERE;
    obj.obj = &sphere;

    int count;
    t_intersection* xs = sphere_intersect(&ray, &obj, &count);

    cr_expect_eq(count, 2, "Expected 0 intersections, got %d", count);
    cr_expect_float_eq(xs[0].t, -1.0, 1e-6, "First intersection point was %f, expected -1.0", xs[0].t);
    cr_expect_float_eq(xs[1].t, 1.0, 1e-6, "Second intersection point was %f, expected 1.0", xs[1].t);
    free(xs);
}

Test(sphere_intersections, sphere_est_derriere_un_rayon) {
    t_ray ray = {point(0, 0, 5), vector(0, 0, 1)};
    t_sphere sphere = sphere_create();
    t_object obj;
    obj.type = SPHERE;
    obj.obj = &sphere;

    int count;
    t_intersection* xs = sphere_intersect(&ray, &obj, &count);

    cr_expect_eq(count, 2, "Expected 0 intersections, got %d", count);
    cr_expect_float_eq(xs[0].t, -6.0, 1e-6, "First intersection point was %f, expected -6.0", xs[0].t);
    cr_expect_float_eq(xs[1].t, -4.0, 1e-6, "Second intersection point was %f, expected -4.0", xs[1].t);
    free(xs);
}

Test(suite_name, test_name) {
    cr_assert(true, "Ce test passe.");
}
