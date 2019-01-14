A = dlmread('traffic.txt');
[n, m] = size(A);
average_vel = (sum(sum(A)) + sum(sum(A<0)))/(m*sum(A(1, :)>=0))
%spy(A)
%sum(A(149,:))
cspy(A+1, 'ColorMap', 'winter', 'Level', 5)
xlabel("x")
ylabel("t")
set(gca,'xtick',[0, m])
set(gca,'xticklabel',[0, m])
set(gca,'ytick',[0, n])
set(gca,'yticklabel',[0, n])
axis tight

%sum(A(13, :)) + sum(A(13, :) < 0)



nonzeroInd = find(A);
[x, y] = ind2sub([m n], nonzeroInd);
[X, Y] = meshgrid(1:m, 1:n);
A = (X + Y) .* A;

figure();
hp = patch(x, y, A(nonzeroInd), ...
           'Marker', 's', 'MarkerFaceColor', 'flat', 'MarkerSize', 4, ...
           'EdgeColor', 'none', 'FaceColor', 'none');
set(gca, 'XLim', [0, m + 1], 'YLim', [0, n + 1], 'YDir', 'reverse', ...
    'PlotBoxAspectRatio', [n + 1, m + 1, 1]);

colorbar();