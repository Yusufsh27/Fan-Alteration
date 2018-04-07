
x = 1.0;
xx = 63.75;
for i = 1:16
    y = (x/5) * 255;
    fprintf([num2str(i) '-->' num2str(x) '-->' num2str(y) '-->' num2str(xx) '\n'])
    x = x + .24;
    xx = xx + 12.75;
end