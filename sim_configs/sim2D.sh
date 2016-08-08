lattice_w=100
lattice_h=100

run_per_set_of_parameters=50

min_p_infect=0
max_p_infect=1
d_p_infect=0.00001

min_p_coinfect=0.01
max_p_coinfect=0.01
d_p_coinfect=0.1

min_p_recover=1.0
max_p_recover=1.0
d_p_recover=0.1

output_dir=output/sim2d.csv

../sim $lattice_w $lattice_h $run_per_set_of_parameters $min_p_infect $max_p_infect $d_p_infect $min_p_coinfect $max_p_coinfect $d_p_coinfect $min_p_recover $max_p_recover $d_p_recover $output_dir
