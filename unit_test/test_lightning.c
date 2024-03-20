#include <criterion/criterion.h>
#include "../include/graphics.h"


Test(suite_name, test_lighting_with_eye_between_light_and_surface) 
{
    t_tuple eyev = vector(0, 0, -1);
    t_tuple normalv = vector(0, 0, -1);
    t_light light = create_light((t_color){1.0, 1.0, 1.0} , point(0, 0, -10));
    t_material m = default_material();
    t_tuple position = point(0, 0, 0);

    t_color result = lighting(m, light, position, eyev, normalv);

    cr_expect_eq(result.r, 1.9, "La composante rouge de la couleur résultante est incorrecte.");
    cr_expect_eq(result.g, 1.9, "La composante verte de la couleur résultante est incorrecte.");
    cr_expect_eq(result.b, 1.9, "La composante bleue de la couleur résultante est incorrecte.");
}

Test(suite_name, Lighting_with_eye_between_light_and_surface_eye_offset_45) 
{
    double sqrt2_over_2 = sqrt(2) / 2;
    t_tuple eyev = vector(0, sqrt2_over_2, -sqrt2_over_2);
    t_tuple normalv = vector(0, 0, -1);
    t_light light = create_light((t_color){1.0, 1.0, 1.0}, point(0, 0, -10));
    t_material m = default_material();
    t_tuple position = point(0, 0, 0);

    t_color result = lighting(m, light, position, eyev, normalv);

    cr_expect_float_eq(result.r, 1.0, 1e-6, "La composante rouge de la couleur résultante est incorrecte.");
    cr_expect_float_eq(result.g, 1.0, 1e-6, "La composante verte de la couleur résultante est incorrecte.");
    cr_expect_float_eq(result.b, 1.0, 1e-6, "La composante bleue de la couleur résultante est incorrecte.");
}

#define EPSILON 0.001

Test(suite_name, Lighting_with_the_eye_opposite_light_offset_45_degrees) {
    t_tuple eyev = vector(0, 0, -1);
    t_tuple normalv = vector(0, 0, -1);
    t_light light = create_light((t_color){255, 255, 255}, point(0, 10, -10));
    t_material m = default_material();
    t_tuple position = point(0, 0, 0);

    t_color result = lighting(m, light, position, eyev, normalv);

    double expected_value = 0.7364 * 255;
    cr_expect_float_eq(result.r, expected_value, EPSILON, "La composante rouge de la couleur résultante est incorrecte.");
    cr_expect_float_eq(result.g, expected_value, EPSILON, "La composante verte de la couleur résultante est incorrecte.");
    cr_expect_float_eq(result.b, expected_value, EPSILON, "La composante bleue de la couleur résultante est incorrecte.");

}

Test(suite_name, Lighting_with_eye_in_path_of_reflection_vector) 
{
    double sqrt2_over_2 = sqrt(2) / 2;
    t_tuple eyev = vector(0, -sqrt2_over_2, -sqrt2_over_2);
    t_tuple normalv = vector(0, 0, -1);
    t_light light = create_light((t_color){1.0, 1.0, 1.0}, point(0, 10, -10));
    t_material m = default_material();
    t_tuple position = point(0, 0, 0);

    t_color result = lighting(m, light, position, eyev, normalv);

    cr_expect_float_eq(result.r, 1.6364, 1e-4, "R component incorrect.");
    cr_expect_float_eq(result.g, 1.6364, 1e-4, "G component incorrect.");
    cr_expect_float_eq(result.b, 1.6364, 1e-4, "B component incorrect.");
}

Test(suite_name, Lighting_with_light_behind_surface) {
    t_tuple eyev = vector(0, 0, -1);
    t_tuple normalv = vector(0, 0, -1);
    t_light light = create_light((t_color){1.0, 1.0, 1.0}, point(0, 0, 10));
    t_material m = default_material();
    t_tuple position = point(0, 0, 0);
    t_color result = lighting(m, light, position, eyev, normalv);
    cr_expect_float_eq(result.r, 0.1, 1e-4, "R component incorrect.");
    cr_expect_float_eq(result.g, 0.1, 1e-4, "G component incorrect.");
    cr_expect_float_eq(result.b, 0.1, 1e-4, "B component incorrect.");
}

