begin
    procedure multiMatriz(a, b, n, m);
        value n, m;
        integer array a, b, r;
        integer n, m;
        begin
            integer i, j, k;

            i := 0;
            k := 0;
            j := 0;

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
                    r[i, j] := somatorio
                 end

        end;
    integer array a[1:2,1:2], b[1:2,1:2];

    a[1,1] := 1;
    a[1,2] := 2;
    a[2,1] := 1;
    a[2,2] := 2;

    b[1,1] := 2;
    b[1,2] := 1;
    b[2,1] := 2;
    b[2,2] := 1;

    multiMatriz(a,b,2,2)
end
