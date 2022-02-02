#include <cstring>
#include <cstdio>
#include "argparse.h"

//	res = m_modifiers.back();
//	m_modifiers.pop_back();

#define IS_PARAM(x) (!strcmp(argv[i],"-" x))

#define ARG_RESOLUTION "res"
#define ARG_THRESHOLD  "threshold"
#define ARG_INVERT     "invert"

env_t::env_t()
    : width(100)
    , height(100)
    , threshold(0.0f)
    , invert(false)
    , filepath(0)
{}

int setup(int argc, char **argv, env_t *env)
{
	for (size_t i = 1; i < (size_t)argc; ++i) {
		if (IS_PARAM(ARG_RESOLUTION)) {
            ++i;
			if (!argv[i]) {
				printf("No value was provided for %s\n", argv[i-1]);
				return 2;
			}

            size_t w, h;
			if (sscanf(argv[i], "%lux%lu", &w, &h) < 2) {
				printf("Invalid %s value. Should be <uint>x<uint>.\n", argv[i-1]);
				return 2;
			}

			if ((w == 0) || (h == 0)) {
				printf("Invalid %s value.\n", argv[i-1]);
				return 2;
			}

            env->width  = w;
            env->height = h;
		}
        else if (IS_PARAM(ARG_INVERT))
        {
            env->invert = true;
        }
        else if (IS_PARAM(ARG_THRESHOLD)) {
            ++i;

            if (!argv[i]) {
                printf("No value was provided for %s\n", argv[i-1]);
                return 2;
            }

            if (sscanf(argv[i], "%f", &(env->threshold)) < 1) {
                printf("Invalid %s value. Should be <float>.\n", argv[i-1]);
            }
        }
		// Invalid argument
		else if (argv[i][0] == '-') {

			printf("Invalid argument: %s\n", argv[i]);
			return 2;
		}
        else {
            if (env->filepath == 0) env->filepath = argv[i];
            else printf("Multiple files given.\n");
        }
	}

	if (env->filepath == 0) return -1;	
	
	return 0;
}
