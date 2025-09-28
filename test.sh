#!/usr/bin/env sh

gcc -o cdenv main.c

cat <<EOF > '.env'
A_KEY=a_key_value
B_KEY=b_key_value
EOF

a_key="$(./cdenv A_KEY)"
if [ "$a_key" != "a_key_value" ]; then
	echo "incorrect value returned for A_KEY: $a_key"
fi

b_key="$(./cdenv B_KEY)"
if [ "$b_key" != "b_key_value" ]; then
	echo "incorrect value returned for B_KEY: $b_key"
fi

no_key="$(./cdenv NO_KEY)"
if [ $? -ne 1 ]; then
	echo "incorrect status code returned for missing key: $?"
fi
