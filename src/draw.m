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
    heapSort_times = times(6 + 15 * (i - 1):10 + 15 * (i - 1));
    fibheapSort_times = times(11 + 15 * (i - 1):15 + 15 * (i - 1));
    bubbleSort_mem = memory(1 + 15 * (i - 1):5 + 15 * (i - 1));
    heapSort_mem = memory(6 + 15 * (i - 1):10 + 15 * (i - 1));
    fiboheapSort_mem = memory(11 + 15 * (i - 1):15 + 15 * (i - 1));
    figure;
    subplot(1, 2, 1); % 左侧绘制时间曲线
    hold on;
    plot(data_sizes, bubbleSort_times, '-o', 'DisplayName', '冒泡排序');
    plot(data_sizes, heapSort_times, '-x', 'DisplayName', '斐波那契堆排序');
    plot(data_sizes, fibHeapSort_times, '-s', 'DisplayName', '堆排序');
    set(gca, 'XScale', 'log'); % 将X轴设为对数刻度
    set(gca, 'YScale', 'log'); % 将Y轴设为对数刻度
    xlabel('数据量');
    ylabel('所用时间 (ms)');
    title('时间');

    subplot(1, 2, 2); % 右侧绘制内存曲线
    hold on;
    plot(data_sizes, bubbleSort_mem, '-o', 'DisplayName', '冒泡排序');
    plot(data_sizes, heapSort_mem, '-x', 'DisplayName', '斐波那契堆排序');
    plot(data_sizes, fibHeapSort_mem, '-s', 'DisplayName', '堆排序');
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