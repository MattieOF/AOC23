program Day2;

uses
    Types, SysUtils, StrUtils;

var
    // Variables for reading the file
    InputFile: text;
    FileBuffer: string;
    
    GameID: integer;

    // Variables used for iterating over parsed game string
    Tokens, Tokens2, Tokens3: TStringDynArray;
    TrimmedElement, Element, Element2: String;
    HighestRed, HighestGreen, HighestBlue: integer;
    Accum: Int32;
    CurrentNum: Integer;

const
    MaxRed = 12;
    MaxGreen = 13;
    MaxBlue = 14;

begin
    Accum := 0;
    assign (InputFile, 'input.txt');
    reset (InputFile);
    while not EOF(InputFile) do
    begin
        HighestRed := 0;
        HighestBlue := 0;
        HighestGreen := 0;

        readln(InputFile, FileBuffer);
        Tokens := StrUtils.SplitString(FileBuffer, ':');
        Tokens2 := StrUtils.SplitString(Tokens[0], ' ');
        GameID := StrToInt(Tokens2[1]);

        Tokens := StrUtils.SplitString(Trim(Tokens[1]), ';');
        for Element in Tokens do
        begin
            Tokens2 := StrUtils.SplitString(Element, ',');
            for Element2 in Tokens2 do
            begin
                TrimmedElement := Trim(Element2);
                Tokens3 := StrUtils.SplitString(TrimmedElement, ' ');
                CurrentNum := StrToInt(Tokens3[0]);

                if CompareText(Tokens3[1], 'red') = 0 then
                begin
                    if (HighestRed < CurrentNum) then
                        HighestRed := CurrentNum;
                end
                else if CompareText(Tokens3[1], 'blue') = 0 then
                begin
                    if (HighestBlue < CurrentNum) then
                        HighestBlue := CurrentNum;
                end
                else if CompareText(Tokens3[1], 'green') = 0 then
                begin
                    if (HighestGreen < CurrentNum) then
                        HighestGreen := CurrentNum;
                end;
            end;
        end;

        write('------------');
        write(GameID);
        writeln('------------');
        write('Highest Red: ');
        writeln(HighestRed);
        write('Highest Blue: ');
        writeln(HighestBlue);
        write('Highest Green: ');
        writeln(HighestGreen);
        write('Power: ');
        writeln(HighestRed * HighestBlue * HighestGreen);
        write('New Total: ');
        Accum := Accum + (HighestRed * HighestBlue * HighestGreen);
        writeln(Accum);
    end;

    writeln('-----------RESULT----------');
    writeln (Accum);

    readln ();
end.
