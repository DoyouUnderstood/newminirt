#include <criterion/criterion.h>
#include "../include/shape.h"

Test(ray_transformation_tests, matrix_translation_of_a_ray) 
{
    t_ray r = ray_create(point(1, 2, 3), vector(0, 1, 0));
    t_matrix m = matrix_translation(3, 4, 5);
    t_ray r2 = ray_transform(m, r);

    cr_assert(tuple_eq(r2.origin, point(4, 6, 8)), "La nouvelle origine du rayon devrait être (4, 6, 8)");
    cr_assert(tuple_eq(r2.direction, vector(0, 1, 0)), "La direction du rayon devrait rester (0, 1, 0)");
}

Test(ray_transformation_tests, matrix_scaling_of_a_ray) {
    t_ray r = ray_create(point(1, 2, 3), vector(0, 1, 0));
    t_matrix m = matrix_scaling(2, 3, 4);
    t_ray r2 = ray_transform(m, r);

    cr_assert(tuple_eq(r2.origin, point(2, 6, 12)), "La nouvelle origine du rayon devrait être (2, 6, 12)");
    cr_assert(tuple_eq(r2.direction, vector(0, 3, 0)), "La nouvelle direction du rayon devrait être (0, 3, 0)");
}

Test(sphere_transformation_tests, default_transformation_of_a_sphere) {
    t_sphere s = sphere_create();
    cr_assert(matrix_is_identity(s.transform), "La transformation par défaut d'une sphère devrait être la matrice identité");
}

Test(sphere_transformation_tests, changing_a_sphere_transformation) {
    t_sphere s = sphere_create();
    t_matrix t = matrix_translation(2, 3, 4);
    set_transform(&s, t);
    cr_assert(is_same_matrice(s.transform, t), "La transformation de la sphère devrait être égale à la translation__matrix (2, 3, 4)");
}

Test(sphere_intersection_tests, intersection_of_a_scaled_sphere_with_a_ray) {
    t_ray r = ray_create(point(0, 0, -5), vector(0, 0, 1));
    t_sphere s = sphere_create();
    set_transform(&s, matrix_scaling(2, 2, 2));
    t_object *obj = object_create_for_sphere(&s);
    int count;
    t_intersection* xs = intersect(&r, obj, &count);
    cr_assert_eq(count, 2, "Le nombre d'intersections devrait être 2");
    cr_assert_float_eq(xs[0].t, 3, 1e-6, "Le premier point d'intersection devrait être à t=3");
    cr_assert_float_eq(xs[1].t, 7, 1e-6, "Le second point d'intersection devrait être à t=7");
    free(xs);
}


Test(sphere_intersection_tests, intersection_of_a_translated_sphere_with_a_ray2) {
    t_ray r = ray_create(point(0, 0, -5), vector(0, 0, 1));
    t_sphere s = sphere_create();
    t_object *obj = object_create_for_sphere(&s);
    set_transform(&s, matrix_translation(5, 0, 0));
    int count;
    t_intersection* xs = intersect(&r, obj, &count);
    cr_assert_eq(count, 0, "Il ne devrait y avoir aucune intersection");
    (void)xs;
}

Test(sphere_intersection_tests, intersection_of_a_translated_sphere_with_a_ray) {
    t_ray r = ray_create(point(0, 0, -5), vector(0, 0, 1));
    t_sphere s = sphere_create();
    t_object *obj;
    t_matrix trans_mat = matrix_translation(5, 0, 0);
    set_transform(&s, trans_mat);
    obj = object_create_for_sphere(&s);
    int count = 0;
    t_intersection* xs = intersect(&r, obj, &count);
    cr_assert_eq(count, 0, "Il ne devrait y avoir aucune intersection");
    (void)xs;
}

