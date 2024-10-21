types = ["bubbleSort", "fibSort", "heapSort"];
options = ["O0","O1","O2","O3","Ofast"];
times = [];
memory = [];

% 读取文件内容并提取数据
for i = 1:75
    % 计算类型索引，并生成路径
    index = ceil(i / 15);
    index2 = i - (index - 1) * 15;
    route = sprintf('../data/result/%s/%s%d.txt', options(index), types(ceil(index2 / 5)), mod(i - 1, 5) + 1);
    
    % 打开文件并检查是否成功
    fileID = fopen(route, 'r');
    if fileID == -1
        warning('无法打开文件: %s', route);
        continue;  
    end

    % 逐行读取文件内容
    while ~feof(fileID)
        line = fgetl(fileID);
        if contains(line, '平均用时')
            time_value = sscanf(line, '平均用时:%fs');
            times = [times; time_value * 1000];  % 追加时间数据
        elseif contains(line, '占用')
            memory_value = sscanf(line, '占用%dKB内存');
            memory = [memory; memory_value];  % 追加内存数据
        end
    end

    % 关闭文件
    fclose(fileID);
end

data_sizes = [10,100,1000,10000,100000];

for i = 1:5
    bubbleSort_times = times(1 + 15 * (i - 1):5 + 15 * (i - 1));
    fibHeapSort_times = times(6 + 15 * (i - 1):10 + 15 * (i - 1));
    heapSort_times = times(11 + 15 * (i - 1):15 + 15 * (i - 1));
    bubbleSort_mem = memory(1 + 15 * (i - 1):5 + 15 * (i - 1));
    fibHeapSort_mem = memory(6 + 15 * (i - 1):10 + 15 * (i - 1));
    heapSort_mem = memory(11 + 15 * (i - 1):15 + 15 * (i - 1));
    figure;
    subplot(1, 2, 1); % 左侧绘制时间曲线
    hold on;
    plot(data_sizes, bubbleSort_times, '-o', 'DisplayName', '冒泡排序');
    plot(data_sizes, fibHeapSort_times, '-x', 'DisplayName', '斐波那契堆排序');
    plot(data_sizes, heapSort_times, '-s', 'DisplayName', '堆排序');
    set(gca, 'XScale', 'log'); % 将X轴设为对数刻度
    set(gca, 'YScale', 'log'); % 将Y轴设为对数刻度
    xlabel('数据量');
    ylabel('所用时间 (ms)');
    title('时间');

    subplot(1, 2, 2); % 右侧绘制内存曲线
    hold on;
    plot(data_sizes, bubbleSort_mem, '-o', 'DisplayName', '冒泡排序');
    plot(data_sizes, fibHeapSort_mem, '-x', 'DisplayName', '斐波那契堆排序');
    plot(data_sizes, heapSort_mem, '-s', 'DisplayName', '堆排序');
    hold off;
    set(gca, 'XScale', 'log'); % 将X轴设为对数刻度
    
    xlabel('数据量');
    ylabel('内存占用 (KB)');
    title('内存');
    legend('show');
    grid on;

    % 调整布局
    sgtitle(options(i));
    route2 = sprintf('../data/result/%s.svg', options(i));
    print(route2, '-dsvg');
end


for i = 1:3
    x = [1,2,3,4,5]; % 创建一个数值型索引
    sortTimes1 = [];
    sortTimes2 = [];
    sortTimes3 = [];
    sortTimes4 = [];
    sortTimes5 = [];
    sortMem1 = [];
    sortMem2 = [];
    sortMem3 = [];
    sortMem4 = [];
    sortMem5 = [];

    for j = 1:5
        sortTimes1 = [sortTimes1;times((i-1) * 25 + 1 + (j-1) * 5)];
        sortTimes2 = [sortTimes2;times((i-1) * 25 + 2 + (j-1) * 5)];
        sortTimes3 = [sortTimes3;times((i-1) * 25 + 3 + (j-1) * 5)];
        sortTimes4 = [sortTimes4;times((i-1) * 25 + 4 + (j-1) * 5)];
        sortTimes5 = [sortTimes5;times((i-1) * 25 + 5 + (j-1) * 5)];
        sortMem1 = [sortMem1;memory((i-1) * 25 + 1 + (j-1) * 5)];
        sortMem2 = [sortMem2;memory((i-1) * 25 + 2 + (j-1) * 5)];
        sortMem3 = [sortMem3;memory((i-1) * 25 + 3 + (j-1) * 5)];
        sortMem4 = [sortMem4;memory((i-1) * 25 + 4 + (j-1) * 5)];
        sortMem5 = [sortMem5;memory((i-1) * 25 + 5 + (j-1) * 5)];
    end

    figure;
    subplot(1, 2, 1); % 左侧绘制时间曲线
    hold on;
    plot(x, sortTimes1, '-o', 'DisplayName', '10');
    plot(x, sortTimes2, '-x', 'DisplayName', '100');
    plot(x, sortTimes3, '-s', 'DisplayName', '1000');
    plot(x, sortTimes4, '-*', 'DisplayName', '10000');
    plot(x, sortTimes5, '-+', 'DisplayName', '100000');
    set(gca, 'XScale', 'log'); % 将X轴设为对数刻度
    set(gca, 'YScale', 'log'); % 将Y轴设为对数刻度
    xticks(x); % 设置 X 轴刻度
    xticklabels(options); % 使用字符串数组作为刻度标签
    xlabel('优化等级');
    ylabel('所用时间 (ms)');
    title('时间');

    subplot(1, 2, 2); % 右侧绘制内存曲线
    hold on;
    plot(x, sortMem1, '-o', 'DisplayName', '10');
    plot(x, sortMem2, '-x', 'DisplayName', '100');
    plot(x, sortMem3, '-s', 'DisplayName', '1000');
    plot(x, sortMem4, '-*', 'DisplayName', '10000');
    plot(x, sortMem5, '-+', 'DisplayName', '100000');
    hold off;
    set(gca, 'XScale', 'log'); % 将X轴设为对数刻度
    
    xticks(x); % 设置 X 轴刻度
    xticklabels(options); % 使用字符串数组作为刻度标签
    xlabel('优化等级');
    ylabel('内存占用 (KB)');
    title('内存');
    legend('show');
    grid on;

    % 调整布局
    sgtitle(types(i));
    route3 = sprintf('../data/result/%s.svg', types(i));
    print(route3, '-dsvg');
end