using Plots
gr()

filename1 = "digit50withoutpivotk=1_3.dat"
filename2 = "digit50withoutpivotk=5_3.dat"
filename3 = "digit50withoutpivotk=25_3.dat"
# filename4 = "digit100withpivotk=75.dat"

anim = Animation()

totalrows = countlines(open(filename1, "r"))
open(filename1, "r") do fp1
    cnt = 0
    x = zeros(Int64, totalrows, 1)
    y = zeros(Int64, totalrows, 1)
    z = zeros(Int64, totalrows, 1)
    for line in eachline(fp1) # 行ごとに読み込む
        cnt += 1
        line = rstrip(line, '\n') # 改行消し。無くても大丈夫。
        u = split(line, " ") # スペース区切りで分割
        u1 = parse(Int64, u[1]) # 文字列を数値に変換
        u2 = parse(Int64, u[2])
        u3 = parse(Int64, u[3])
        x[cnt] = u1
        y[cnt] = u2
        z[cnt] = u3
    end
    plt = scatter(x, y, z,label = filename1, legend = :left)

    frame(anim, plt)
end
totalrows = countlines(open(filename2, "r"))
open(filename2, "r") do fp1
    cnt = 0
    x = zeros(Int64, totalrows, 1)
    y = zeros(Int64, totalrows, 1)
    z = zeros(Int64, totalrows, 1)
    for line in eachline(fp1) # 行ごとに読み込む
        cnt += 1
        line = rstrip(line, '\n') # 改行消し。無くても大丈夫。
        u = split(line, " ") # スペース区切りで分割
        u1 = parse(Int64, u[1]) # 文字列を数値に変換
        u2 = parse(Int64, u[2])
        u3 = parse(Int64, u[3])
        x[cnt] = u1
        y[cnt] = u2
        z[cnt] = u3
    end
    plt = scatter(x, y, z,label = filename2, legend = :left)

    frame(anim, plt)
end
totalrows = countlines(open(filename3, "r"))
open(filename3, "r") do fp1
    cnt = 0
    x = zeros(Int64, totalrows, 1)
    y = zeros(Int64, totalrows, 1)
    z = zeros(Int64, totalrows, 1)
    for line in eachline(fp1) # 行ごとに読み込む
        cnt += 1
        line = rstrip(line, '\n') # 改行消し。無くても大丈夫。
        u = split(line, " ") # スペース区切りで分割
        u1 = parse(Int64, u[1]) # 文字列を数値に変換
        u2 = parse(Int64, u[2])
        u3 = parse(Int64, u[3])
        x[cnt] = u1
        y[cnt] = u2
        z[cnt] = u3
    end
    plt = scatter(x, y, z,label = filename3, legend = :left)

    frame(anim, plt)
end
# totalrows = countlines(open(filename4, "r"))
# open(filename4, "r") do fp1
#     cnt = 0
#     x = zeros(Int64, totalrows, 1)
#     y = zeros(Int64, totalrows, 1)
#     z = zeros(Int64, totalrows, 1)
#     for line in eachline(fp1) # 行ごとに読み込む
#         cnt += 1
#         line = rstrip(line, '\n') # 改行消し。無くても大丈夫。
#         u = split(line, " ") # スペース区切りで分割
#         u1 = parse(Int64, u[1]) # 文字列を数値に変換
#         u2 = parse(Int64, u[2])
#         u3 = parse(Int64, u[3])
#         x[cnt] = u1
#         y[cnt] = u2
#         z[cnt] = u3
#     end
#     plt = scatter(x, y, z,label = filename4, legend = :left)
#
#     frame(anim, plt)
# end

gif(anim, "hilbelt2.gif", fps = 1)
