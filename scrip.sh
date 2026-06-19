# Ejecuta 20 veces y guarda cada resultado en un archivo
for i in {1..100}; do ./test_printf >> resultados_printf.txt; done
for i in {1..100}; do ./test_write >> resultados_write.txt; done
