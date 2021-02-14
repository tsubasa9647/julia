using LinearAlgebra

function mylu(xs::Matrix{Float64})
    n = size(xs, 1)
    zs = copy(xs)
    for i = 1 : n
        for j = i + 1 : n
            temp = zs[j, i] / zs[i, i]
            for k = i + 1 : n
                zs[j, k] -= temp * zs[i, k]
            end
            zs[j, i] = temp
        end
    end
    zs
end

function mylu_solver(xs::Matrix{Float64}, ys::Vector{Float64})
    n = size(xs, 1)
    zs = copy(ys)
    # 前進代入
    for i = 2 : n, j = 1 : i - 1
        zs[i] -= xs[i, j] * zs[j]
    end
    # 後退代入
    for i = n : -1 : 1
       for j = i + 1 : n
           zs[i] -= xs[i, j] * zs[j]
       end
       zs[i] /= xs[i, i]
    end
    zs
end

# ピボット選択
function select_pivot(xs::Matrix{Float64}, idx::Vector{Int}, i::Int)
    _, k = findmax(abs.(xs[i:end, i]))
    k += i - 1
    if k != i
        temp = xs[i, :]
        xs[i, :] = xs[k, :]
        xs[k, :] = temp
        idx[i], idx[k] = idx[k], idx[i]
    end
end

function mylu_pv(xs::Matrix{Float64})
    n = size(xs, 1)
    zs = copy(xs)
    idx = collect(1 : n)
    for i = 1 : n
        select_pivot(zs, idx, i)
        for j = i + 1 : n
            temp = zs[j, i] / zs[i, i]
            for k = i + 1 : n
                zs[j, k] -= temp * zs[i, k]
            end
            zs[j, i] = temp
        end
    end
    zs, idx
end

function mylu_solver_pv(xs::Matrix{Float64}, idx::Vector{Int}, ys::Vector{Float64})
    mylu_solver(xs, ys[idx])
end

function mycholesky(xs::Matrix{Float64)
    n = size(xs, 1)
    zs = zeros(n,n)
    for i = 1 : n
        for k = 1 : i
            temp = 0.0
            for j = 1 : k
                temp += zs[i,j] * zs[k,j]
            end
            zs[i,k] = (i == k) ? sqrt(xs[i,i] - temp) : (1.0 / zs[k,k] * (xs[i,k] - temp))
        end
    end
    zs
end

function mycholesky_solver(xs::Matrix{Float64}, ys::Vector{Float64})
    n = size(xs, 1)
    zs = copy(ys)
    xst = transpose(xs)
    # 前進代入
    for i = 2 : n, j = 1 : i - 1
        zs[i] -= xs[i, j] * zs[j]
    end
    # 後退代入
    for i = n : -1 : 1
       for j = i + 1 : n
           zs[i] -= xst[i, j] * zs[j]
       end
       zs[i] /= xst[i, i]
    end
    zs
end

N = 3
a6 = randn(N,N)
b6 = randn(N)

a1 = [1. 1.; 2. 4.]
a2 = [1. 1. 1.; 2. 4. 6.; 2. 0. 4.]
a3 = [1. 1. 1. 1.; -1. 1. -1. 1.; 8. 4. 2. 1.; -8. 4. -2. 1.]
a4 = [1. -1. 1. -1. 1.; 12. -6. 2. 0. 0.; 1. 1. 1. 1. 1.; 12. 6. 2. 0. 0.; 4. 3. 2. 1. 0.]
b1 = [100., 272.]
b2 = [10., 38., 14.]
b3 = [-5., -7., -31., -35.]
b4 = [1., 0., 8., 0., 1.]
for (a, b) = zip([a1, a2, a3, a4, a6], [b1, b2, b3, b4, b6])
    xs = mylu(a)
    println(xs)
    answer = mylu_solver(xs, b)
    println(answer)
    print("誤差:")
    println(a*answer - b)
    println("--------")
end

a1 = [1. 1.; 2. 4.]
a2 = [1. 1. 1.; 2. 4. 6.; 2. 0. 4.]
a3 = [1. 1. 1. 1.; -1. 1. -1. 1.; 8. 4. 2. 1.; -8. 4. -2. 1.]
a4 = [1. -1. 1. -1. 1.; 12. -6. 2. 0. 0.; 1. 1. 1. 1. 1.; 12. 6. 2. 0. 0.; 4. 3. 2. 1. 0.]
a5 = [0. 2. 4.; 1. 1. 1.; 4. 2. 6.]
b1 = [100., 272.]
b2 = [10., 38., 14.]
b3 = [-5., -7., -31., -35.]
b4 = [1., 0., 8., 0., 1.]
b5 = [14., 10., 38.]
for (a, b) = zip([a1, a2, a3, a4, a5, a6], [b1, b2, b3, b4, b5, b6])
    xs, idx = mylu_pv(a)
    println(xs)
    println(idx)
    answer = mylu_solver_pv(xs, idx, b)
    println(answer)
    print("誤差:")
    println(a*answer - b)
    println("--------")
end

aa = [25.0 15.0 -5.0; 15.0 18.0 0.0; -5.0 0.0 11.0]
bb = [18.0 22 54 22; 22 70 86 62; 54 86 174 134; 42 62 134 106]
ch = mycholesky(aaa)
xa=mycholesky_solver(ch,b2)
