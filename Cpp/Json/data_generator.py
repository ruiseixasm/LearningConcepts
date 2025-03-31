from fractions import Fraction
import json


numerator_number: int = int(10)
denominator_number: int = int(123456)


floats_list_100: list[float] = []

for n in range(100):
    floats_list_100.append(
        round(float(n * numerator_number * 60_000 / denominator_number), 3)
    )

print(floats_list_100)

# Serializing json
json_object = json.dumps(floats_list_100)

# Writing to sample.json
with open("Cpp/Json/list_of_floats_3.json", "w") as outfile:
	outfile.write(json_object)

