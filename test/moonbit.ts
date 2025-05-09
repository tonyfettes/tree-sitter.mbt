import type * as MoonBit from "./target/js/release/build/moonbit";
export type { Unit, Result } from "./target/js/release/build/moonbit";

export type AsyncError<T extends (...args: any) => any> = (
  ...args: [
    ...Parameters<T>,
    (result: ReturnType<T>) => MoonBit.Unit,
    (reason?: any) => MoonBit.Unit
  ]
) => MoonBit.Unit;

type Promisified<T extends (...args: any) => any> = (
  ...args: Parameters<T>
) => Promise<ReturnType<T>>;

export function promisify<T extends (...args: any[]) => any>(
  fn: AsyncError<T>
): Promisified<T> {
  return (...args: Parameters<T>): Promise<ReturnType<T>> => {
    return new Promise<ReturnType<T>>((resolve, reject) => {
      fn(
        ...args,
        (result: ReturnType<T>) => {
          resolve(result);
        },
        (reason?: any) => {
          reject(reason);
        }
      );
    });
  };
}
