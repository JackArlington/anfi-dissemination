function [ indices ] = filter_data(data,measure)
indices = find(cellfun('length',regexp(data,measure)) == 1);
end

