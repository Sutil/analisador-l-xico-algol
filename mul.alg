begin
procedure multiMatriz(a, b, n, m);
    value n, m; integer array a, b, r; integer n, m;
begin
    integer i, j, k; 
    
    i := k := j := 0;

    for i := 1 step 1 until n do
        for q := 1 step 1 until m do
        begin
            integer somatorio;
            somatorio := 0;
            for k:= 1 step 1 until m do
                begin
                    integer produto;
                    produto := a[i,k] * b[k, j];
                    somatorio := somatorio + produto
                end;
            r[i, j] := somatori
         end
end;
a := b
end 

