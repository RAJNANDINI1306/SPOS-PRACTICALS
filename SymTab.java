import java.io.*;

class SymTab {

  public static void main(String args[]) throws Exception {
    String filePath = "Inputfile.txt"; // Hardcoded file path for testing

    FileReader FP = new FileReader(filePath);
    BufferedReader bufferedReader = new BufferedReader(FP);

    String line = null;
    int line_count = 0, LC = 0, symTabLine = 0, opTabLine = 0, litTabLine =
      0, poolTabLine = 0;

    // Data Structures
    final int MAX = 100;
    String SymbolTab[][] = new String[MAX][3];
    String OpTab[][] = new String[MAX][3];
    String LitTab[][] = new String[MAX][2];
    int PoolTab[] = new int[MAX];
    boolean isLiteralPresent = false;
    System.out.println("_");
    while ((line = bufferedReader.readLine()) != null) {
      String[] tokens = line.split("\t");
      if (tokens.length == 0) continue; // Skip empty lines
      if (line_count == 0) {
        LC = Integer.parseInt(tokens[1]);
        for (int i = 0; i < tokens.length; i++) {
          System.out.print(tokens[i] + "\t");
        }
        System.out.println("");
      } else {
        for (int i = 0; i < tokens.length; i++) {
          System.out.print(tokens[i] + "\t");
        }
        System.out.println("");

        if (tokens.length > 0 && !tokens[0].equals("")) {
          // Inserting into Symbol Table
          SymbolTab[symTabLine][0] = tokens[0];
          SymbolTab[symTabLine][1] = Integer.toString(LC);
          SymbolTab[symTabLine][2] = Integer.toString(1);
          symTabLine++;
        }
        if (tokens.length > 1) {
          if (
            tokens[1].equalsIgnoreCase("DS") || tokens[1].equalsIgnoreCase("DC")
          ) {
            // Entry into symbol table for declarative statements
            SymbolTab[symTabLine][0] = tokens[0];
            SymbolTab[symTabLine][1] = Integer.toString(LC);
            SymbolTab[symTabLine][2] = Integer.toString(1);
            symTabLine++;
          }
          if (tokens.length > 2 && tokens[2].charAt(0) == '=') {
            // Entry of literals into literal table
            LitTab[litTabLine][0] = tokens[2];
            LitTab[litTabLine][1] = null; // Address will be assigned later
            litTabLine++;
            isLiteralPresent = true;
          }
          // Entry of Mnemonic in opcode table
          OpTab[opTabLine][0] = tokens[1];
          if (
            tokens[1].equalsIgnoreCase("START") ||
            tokens[1].equalsIgnoreCase("END") ||
            tokens[1].equalsIgnoreCase("ORIGIN") ||
            tokens[1].equalsIgnoreCase("EQU") ||
            tokens[1].equalsIgnoreCase("LTORG")
          ) {
            OpTab[opTabLine][1] = "AD";
            OpTab[opTabLine][2] = "R11";
            // Assign addresses to literals on LTORG or END
            if (
              tokens[1].equalsIgnoreCase("LTORG") ||
              tokens[1].equalsIgnoreCase("END")
            ) {
              if (isLiteralPresent) {
                PoolTab[poolTabLine] = litTabLine - (litTabLine > 0 ? 1 : 0);
                poolTabLine++;
                for (int i = 0; i < litTabLine; i++) {
                  if (LitTab[i][1] == null) {
                    LitTab[i][1] = Integer.toString(LC);
                    LC++;
                  }
                }
                isLiteralPresent = false;
              }
            }
          } else if (
            tokens[1].equalsIgnoreCase("DS") || tokens[1].equalsIgnoreCase("DC")
          ) {
            OpTab[opTabLine][1] = "DL";
            OpTab[opTabLine][2] = "R7";
          } else {
            OpTab[opTabLine][1] = "IS";
            OpTab[opTabLine][2] = "(04,1)";
          }
          opTabLine++;
        }
      }
      line_count++;
      LC++;
    }
    System.out.println("_");
    // Print Symbol Table
    System.out.println("\n\n\tSYMBOL TABLE\t\t");
    System.out.println("--------------------------");
    System.out.println("SYMBOL\tADDRESS\tLENGTH");
    System.out.println("--------------------------");
    for (int i = 0; i < symTabLine; i++) {
      System.out.println(
        SymbolTab[i][0] + "\t" + SymbolTab[i][1] + "\t" + SymbolTab[i][2]
      );
    }
    System.out.println("--------------------------");
    // Print Opcode Table
    System.out.println("\n\n\tOPCODE TABLE\t\t");
    System.out.println("----------------------------");
    System.out.println("MNEMONIC\tCLASS\tINFO");
    System.out.println("----------------------------");
    for (int i = 0; i < opTabLine; i++) {
      System.out.println(
        OpTab[i][0] + "\t\t" + OpTab[i][1] + "\t" + OpTab[i][2]
      );
    }
    System.out.println("----------------------------");
    // Print Literal Table
    System.out.println("\n\n   LITERAL TABLE\t\t");
    System.out.println("-----------------");
    System.out.println("LITERAL\tADDRESS");
    System.out.println("-----------------");
    for (int i = 0; i < litTabLine; i++) {
      System.out.println(LitTab[i][0] + "\t" + LitTab[i][1]);
    }
    System.out.println("------------------");
    // Print Pool Table
    System.out.println("\n\n   POOL TABLE\t\t");
    System.out.println("-----------------");
    System.out.println("POOL START");
    System.out.println("-----------------");
    for (int i = 0; i < poolTabLine; i++) {
      System.out.println(PoolTab[i]);
    }
    System.out.println("------------------");
    // Always close files.
    bufferedReader.close();
  }
}
