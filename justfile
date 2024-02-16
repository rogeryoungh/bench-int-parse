test-isd:
	cd src/test && just test-isd

test-swar:
	cd src/test && just test-swar

bench-isd:
	cd src/bench1 && just bench

bench-isd-0:
	cd src/bench1 && just bench-gcc-o2

bench-swar:
	cd src/bench2 && just bench

bench-swar-0:
	cd src/bench2 && just bench-gcc-o2

