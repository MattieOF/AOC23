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
    Impossible: Boolean;
    Accum: Integer;

    numRed: integer;
    numGreen: integer;
    numBlue: integer;

const
    MaxRed = 12;
    MaxGreen = 13;
    MaxBlue = 14;

begin
    assign (InputFile, 'input.txt');
    reset (InputFile);
    while not EOF(InputFile) do
    begin
        Impossible := False;
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
                if CompareText(Tokens3[1], 'red') = 0 then
                begin
                    if (StrToInt(Tokens3[0]) > MaxRed) then
                    begin
                        Impossible := True;
                        break;
                    end;
                end
                else if CompareText(Tokens3[1], 'blue') = 0 then
                begin
                    if (StrToInt(Tokens3[0]) > MaxBlue) then
                    begin
                        Impossible := True;
                        break;
                    end;
                end
                else if CompareText(Tokens3[1], 'green') = 0 then
                begin
                    if (StrToInt(Tokens3[0]) > MaxGreen) then
                    begin
                        Impossible := True;
                        break;
                    end;
                end;
            end;

            if Impossible = True then
                break;
        end;

        if Impossible = False then
        begin
            writeln (GameID);
            Accum := Accum + GameID;
        end;
    end;

    writeln (Accum);

    readln ();
end.
