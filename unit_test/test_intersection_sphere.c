#include <criterion/criterion.h>
#include "../include/shape.h"

Test(sphere_intersections, ray_intersects_sphere_at_two_points) 
{
    t_ray ray = {point(0, 0, -5), vector(0, 0, 1)};
    t_sphere sphere = create_sphere();
    t_intersection xs = intersect_sphere(&ray, &sphere);

    cr_expect_eq(xs.count, 2, "Expected 2 intersections, got %d", xs.count);
    cr_expect_float_eq(xs.t[0], 4.0, 1e-6, "First intersection point was %f, expected 4.0", xs.t[0]);
    cr_expect_float_eq(xs.t[1], 6.0, 1e-6, "Second intersection point was %f, expected 6.0", xs.t[1]);
}

Test(sphere_intersections, ray_intersects_sphere_selon_une_tangente) 
{
    t_ray ray = {point(0, 1, -5), vector(0, 0, 1)};
    t_sphere sphere = create_sphere();
    t_intersection xs = intersect_sphere(&ray, &sphere);

    cr_expect_eq(xs.count, 2, "Expected 2 intersections, got %d", xs.count);
    cr_expect_float_eq(xs.t[0], 5.0, 1e-6, "First intersection point was %f, expected 5.0", xs.t[0]);
    cr_expect_float_eq(xs.t[1], 5.0, 1e-6, "Second intersection point was %f, expected 5.0", xs.t[1]);
}

Test(sphere_intersections, ray_intersects_sphere_at_nothin_he_miss) 
{
    t_ray ray = {point(0, 2, -5), vector(0, 0, 1)};
    t_sphere sphere = create_sphere();
    t_intersection xs = intersect_sphere(&ray, &sphere);

    cr_expect_eq(xs.count, 0, "Expected 0 intersections, got %d", xs.count);
}

Test(sphere_intersections, ray_rayon_prend_naissance_à_l_intérieur_d_une_sphère) 
{
    t_ray ray = {point(0, 0, 0), vector(0, 0, 1)};
    t_sphere sphere = create_sphere();
    t_intersection xs = intersect_sphere(&ray, &sphere);

    cr_expect_eq(xs.count, 2, "Expected 2 intersections, got %d", xs.count);
    cr_expect_float_eq(xs.t[0], -1.0, 1e-6, "First intersection point was %f, expected -1.0", xs.t[0]);
    cr_expect_float_eq(xs.t[1], 1.0, 1e-6, "Second intersection point was %f, expected 1.0", xs.t[1]);
}

Test(sphere_intersections, sphere_est_derriere_un_rayon) 
{
    t_ray ray = {point(0, 0, 5), vector(0, 0, 1)};
    t_sphere sphere = create_sphere();
    t_intersection xs = intersect_sphere(&ray, &sphere);

    cr_expect_eq(xs.count, 2, "Expected 2 intersections, got %d", xs.count);
    cr_expect_float_eq(xs.t[0], -6.0, 1e-6, "First intersection point was %f, expected -6.0", xs.t[0]);
    cr_expect_float_eq(xs.t[1], -4.0, 1e-6, "Second intersection point was %f, expected -4.0", xs.t[1]);
}


Test(suite_name, test_name) {
    cr_assert(true, "Ce test passe.");
}
