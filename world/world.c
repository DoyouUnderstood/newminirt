#include "../include/main.h"

#include "../include/graphics.h"
#include "../include/mathematique.h"
#include "../include/shape.h"

#define MAX_OBJECTS 10

t_color shade_hit(t_world *world, t_computations *comps)
{
    t_sphere *sphere = (t_sphere *)(world->objects[0]->obj);
    t_color color = lighting(&sphere->material, world->light, &comps->point, &comps->eyev, &comps->normalv);
    return color;
}

t_computations prepare_computations(const t_intersection *intersection, t_ray *ray) {
    t_computations comps;
    comps.t = intersection->t;
    comps.object = intersection->object;
    comps.point = t_point_position(*ray, intersection->t);
    comps.eyev = vector_negate(ray->direction);
    comps.normalv = normal_at((t_sphere*)(intersection->object), comps.point);

    if (vector_dot(comps.normalv, comps.eyev) < 0) {
        comps.inside = true;
        comps.normalv = vector_negate(comps.normalv);
    } else {
        comps.inside = false;
    }

    return comps;
}


void world_add_object(t_world* world, t_object* object) {
    if (world->object_count < MAX_OBJECTS) {
        world->objects[world->object_count++] = object;
    } else {
        error_exit("le monde a atteint son maximum faut enlever des objects l'ami");
    }
}


t_world* world_create() {
    t_world* w = malloc(sizeof(t_world));
    if (!w) 
        return NULL;
    
    w->light = NULL;
    w->object_count = 0;
    w->objects = malloc(MAX_OBJECTS * sizeof(t_object*));
    if (!w->objects) {
        free(w);
        return NULL;
    }
    for (int i = 0; i < MAX_OBJECTS; i++) {
        w->objects[i] = NULL;
    }
    return w;
}


// Define the default world
t_world* world_default() {
    t_world* w = world_create();
    if (!w) return NULL;

    t_tuple light_position = point_create(-10, 10, -10);
    t_color light_color = {1, 1, 1};
    t_light* light = light_create(light_color, light_position);
    w->light = light;
    t_sphere* s1 = sphere_create();
    s1->material.color = (t_color){0.8, 1.0, 0.6};
    s1->material.diffuse = 0.7;
    s1->material.specular = 0.2;
    t_object* obj1 = malloc(sizeof(t_object));
    obj1->type = SPHERE;
    obj1->obj = s1;
    world_add_object(w, obj1);
    t_sphere* s2 = sphere_create();
    s2->transform = matrix_scaling(0.5, 0.5, 0.5);
    t_object* obj2 = malloc(sizeof(t_object));
    obj2->type = SPHERE;
    obj2->obj = s2;
    world_add_object(w, obj2);

    return w;
}


int compare_intersections(const void* a, const void* b) 
{
    t_intersection* ia = (t_intersection*)a;
    t_intersection* ib = (t_intersection*)b;
    if (ia->t < ib->t) return -1;
    else if (ia->t > ib->t) return 1;
    else return 0;
}

void world_destroy(t_world* world) {
    if (!world) 
        return;
    for (int i = 0; i < world->object_count; i++) {
        free(world->objects[i]);
    }
    free(world->objects);
    free(world);
}


t_intersection* intersect_world(const t_world* world, const t_ray* ray, int* count) {
    *count = 0;
    int capacity = 10;
    t_intersection* intersections = malloc(capacity * sizeof(t_intersection));
    if (!intersections) 
        return NULL;

    for (int i = 0; i < world->object_count; i++) {
        int local_count = 0;
        t_intersection* local_intersections = intersect(ray, world->objects[i], &local_count);

        while (*count + local_count > capacity) {
            capacity *= 2;
            intersections = realloc(intersections, capacity * sizeof(t_intersection));
            if (!intersections) 
                return NULL;
        }

        for (int j = 0; j < local_count; j++) {
            intersections[*count + j] = local_intersections[j];
        }
        *count += local_count;

        free(local_intersections);
    }

    qsort(intersections, *count, sizeof(t_intersection), compare_intersections);

    return intersections;
}

