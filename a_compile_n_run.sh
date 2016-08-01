lattice_w = 100;
lattice_h = 100;

init_infection_1_pos_x = 50;
init_infection_1_pos_y = 50;
init_infection_2_pos_x = 80;
init_infection_2_pos_y = 80;

run_per_set_of_parameters = atoi(args[1]);

min_p_infect = 0;
max_p_infect = 1;
d_p_infect = atof(args[2]);

min_p_coinfect = 0.99;
max_p_coinfect = 0.99;
d_p_coinfect = atof(args[3]);

min_p_recover = 1.0;
max_p_recover = 1.0;
d_p_recover = 0.1;

p_infect = min_p_infect;
p_coinfect = min_p_coinfect;
p_recover = min_p_recover;

make -f 'makefile.analytics'
./sim 1000 0.01 0.1
