function [ output ] = filter_zero_values( input )
output = input(input ~= 0);
end

